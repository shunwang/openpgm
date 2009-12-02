/* vim:ts=8:sts=8:sw=4:noai:noexpandtab
 * 
 * 32-bit atomic operations.
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

#ifndef __PGM_ATOMIC_H__
#define __PGM_ATOMIC_H__

#include <glib.h>


G_BEGIN_DECLS

#ifndef G_STATIC_ASSERT
#	define G_PASTE_ARGS(identifier1,identifier2) identifier1 ## identifier2
#	define G_PASTE(identifier1,identifier2) G_PASTE_ARGS (identifier1, identifier2)
#	define G_STATIC_ASSERT(expr) typedef struct { char Compile_Time_Assertion[(expr) ? 1 : -1]; } G_PASTE (_GStaticAssert_, __LINE__)
#endif

G_STATIC_ASSERT(sizeof(gint) == sizeof(gint32));

static inline void pgm_atomic_int32_add (volatile gint32* atomic, const gint32 val)
{
	g_atomic_int_add (atomic, val);
}

static inline gint32 pgm_atomic_int32_get (volatile gint32* atomic)
{
	return g_atomic_int_get (atomic);
}

static inline void pgm_atomic_int32_set (volatile gint32* atomic, const gint32 newval)
{
	g_atomic_int_set (atomic, newval);
}

#ifndef G_ATOMIC_OP_MEMORY_BARRIER_NEEDED
#	define pgm_atomic_int32_get(atomic) 		(*(atomic))
#	define pgm_atomic_int32_set(atomic, newval) 	((void) (*(atomic) = (newval)))
#endif /* G_ATOMIC_OP_MEMORY_BARRIER_NEEDED */

#define pgm_atomic_int32_inc(atomic) (pgm_atomic_int32_add ((atomic), 1))

G_END_DECLS

#endif /* __PGM_ATOMIC_H__ */
