/* vim:ts=8:sts=8:sw=4:noai:noexpandtab
 *
 * unit tests for high resolution timers.
 *
 * Copyright (c) 2009 Miru Limited.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <glib.h>
#include <check.h>


/* mock state */


/* mock functions for external references */


#include "time.c"


/* target:
 *	gboolean
 *	pgm_time_init (GError** error)
 */

START_TEST (test_init_pass_001)
{
	fail_unless (TRUE == pgm_time_init (NULL));
	fail_unless (FALSE == pgm_time_init (NULL));
}
END_TEST

/* target:
 *	gboolean
 *	pgm_time_shutdown (void)
 */

START_TEST (test_shutdown_pass_001)
{
	fail_unless (TRUE == pgm_time_init (NULL));
	fail_unless (TRUE == pgm_time_shutdown ());
	fail_unless (FALSE == pgm_time_shutdown ());
}
END_TEST

/* target:
 *	gboolean
 *	pgm_time_supported (void)
 */

START_TEST (test_supported_pass_001)
{
	fail_unless (FALSE == pgm_time_supported ());
	fail_unless (TRUE == pgm_time_init (NULL));
	fail_unless (TRUE == pgm_time_supported ());
	fail_unless (TRUE == pgm_time_shutdown ());
	fail_unless (FALSE == pgm_time_supported ());
}
END_TEST

/* target:
 *	pgm_time_t
 *	pgm_time_update_now (void)
 */

START_TEST (test_update_now_pass_001)
{
	pgm_time_t tstamps[11];
	fail_unless (TRUE == pgm_time_init (NULL));
	const pgm_time_t start_time = pgm_time_update_now ();
	for (unsigned i = 1; i <= 10; i++)
	{
		tstamps[i] = pgm_time_update_now();
	}
	g_message ("start-time:     %" PGM_TIME_FORMAT, start_time);
	for (unsigned i = 1; i <= 10; i++)
	{
		const pgm_time_t check_time = tstamps[i];
		const gint64 elapsed_time = check_time - start_time;

/* must be monotonic */
		fail_unless (G_LIKELY(check_time >= start_time));

		g_message ("check-point-%2.2u: %" PGM_TIME_FORMAT " (%+" G_GINT64_FORMAT "us)",
			   i, check_time, pgm_to_usecs(elapsed_time));
	}
	fail_unless (TRUE == pgm_time_shutdown ());
}
END_TEST

/* target:
 *	void
 *	pgm_time_sleep (
 *		gulong		usec
 *		)
 */

START_TEST (test_sleep_pass_001)
{
	pgm_time_t tstamps[11];
	const pgm_time_t sleep_time = 100 * 1000;	/* 100ms */
	fail_unless (TRUE == pgm_time_init (NULL));
	pgm_time_t start_time = pgm_time_update_now ();
	for (unsigned i = 1; i <= 10; i++)
	{
		tstamps[i] = pgm_time_sleep (sleep_time);
	}
	g_message ("start-time:     %" PGM_TIME_FORMAT, start_time);
	for (unsigned i = 1; i <= 10; i++)
	{
		const pgm_time_t check_time = tstamps[i];

		fail_unless (check_time >= start_time);
		const gint64 elapsed_time = check_time - start_time;

/* should be close to zero */
		const gint64 diff_time = elapsed_time - sleep_time;
		const float percent_diff = ( 100.0 * pgm_to_usecsf (diff_time) ) / sleep_time;
		g_message ("check-point-%2.2u: %" PGM_TIME_FORMAT " (%+" G_GINT64_FORMAT "us %+3.1f%%)",
			   i, check_time, pgm_to_usecs(elapsed_time), percent_diff);

		start_time = check_time;
	}
	fail_unless (TRUE == pgm_time_shutdown ());
}
END_TEST

/* target:
 *	void
 *	pgm_time_since_epoch (
 *		pgm_time_t*	pgm_time,
 *		time_t*		epoch_time
 *		)
 */

START_TEST (test_since_epoch_pass_001)
{
	char stime[1024];
	time_t t;
	struct tm* tmp;
	fail_unless (TRUE == pgm_time_init (NULL));
	pgm_time_t pgm_now = pgm_time_update_now ();
	pgm_time_since_epoch (&pgm_now, &t);
	tmp = localtime (&t);
	fail_unless (NULL != tmp);
	fail_unless (0 != strftime (stime, sizeof(stime), "%X", tmp));
	g_message ("pgm-time:%" PGM_TIME_FORMAT " = %s",
		   pgm_now, stime);
	fail_unless (TRUE == pgm_time_shutdown ());
}
END_TEST


static
Suite*
make_test_suite (void)
{
	Suite* s;

	s = suite_create (__FILE__);

	TCase* tc_init = tcase_create ("init");
	suite_add_tcase (s, tc_init);
	tcase_add_test (tc_init, test_init_pass_001);

	TCase* tc_shutdown = tcase_create ("shutdown");
	suite_add_tcase (s, tc_shutdown);
	tcase_add_test (tc_shutdown, test_shutdown_pass_001);

	TCase* tc_supported = tcase_create ("supported");
	suite_add_tcase (s, tc_supported);
	tcase_add_test (tc_supported, test_supported_pass_001);

	TCase* tc_update_now = tcase_create ("update-now");
	suite_add_tcase (s, tc_update_now);
	tcase_add_test (tc_update_now, test_update_now_pass_001);

	TCase* tc_sleep = tcase_create ("sleep");
	suite_add_tcase (s, tc_sleep);
	tcase_add_test (tc_sleep, test_sleep_pass_001);

	TCase* tc_since_epoch = tcase_create ("since-epoch");
	suite_add_tcase (s, tc_since_epoch);
	tcase_add_test (tc_since_epoch, test_since_epoch_pass_001);
	return s;
}

static
Suite*
make_master_suite (void)
{
	Suite* s = suite_create ("Master");
	return s;
}

int
main (void)
{
//	setenv ("PGM_TIMER", "GTOD", 1);
	setenv ("PGM_TIMER", "HPET", 1);
	setenv ("PGM_SLEEP", "USLEEP", 1);

	SRunner* sr = srunner_create (make_master_suite ());
	srunner_add_suite (sr, make_test_suite ());
	srunner_run_all (sr, CK_ENV);
	int number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* eof */