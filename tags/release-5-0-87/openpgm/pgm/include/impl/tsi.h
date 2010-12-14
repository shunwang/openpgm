/* vim:ts=8:sts=4:sw=4:noai:noexpandtab
 * 
 * transport session ID helper functions
 *
 * Copyright (c) 2006-2010 Miru Limited.
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

#if !defined (__PGM_IMPL_FRAMEWORK_H_INSIDE__) && !defined (PGM_COMPILATION)
#       error "Only <framework.h> can be included directly."
#endif

#pragma once
#ifndef __PGM_IMPL_TSI_H__
#define __PGM_IMPL_TSI_H__

#include <pgm/types.h>
#include <pgm/tsi.h>
#include <impl/hashtable.h>

PGM_BEGIN_DECLS

PGM_GNUC_INTERNAL pgm_hash_t pgm_tsi_hash (const void*) PGM_GNUC_WARN_UNUSED_RESULT;

PGM_END_DECLS

#endif /* __PGM_IMPL_TSI_H__ */