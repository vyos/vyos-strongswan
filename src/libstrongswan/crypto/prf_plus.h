/**
 * @file prf_plus.h
 * 
 * @brief Interface for prf_plus.h.
 * 
 */

/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef PRF_PLUS_H_
#define PRF_PLUS_H_

typedef struct prf_plus_t prf_plus_t;

#include <crypto/prfs/prf.h>

/**
 * @brief Implementation of the prf+ function described in IKEv2 RFC.
 *
 * This class implements the prf+ algorithm. Internally it uses a pseudo random
 * function, which implements the prf_t interface.
 * 
 * See IKEv2 RFC 2.13.
 * 
 * @b Constructors:
 *  - prf_plus_create()
 * 
 * @ingroup transforms
 */
struct prf_plus_t {
	/**
	 * @brief Get pseudo random bytes.
	 * 
	 * Get the next few bytes of the prf+ output. Space
	 * must be allocated by the caller.
	 * 
	 * @param this			calling object
	 * @param length		number of bytes to get
	 * @param[out] buffer	pointer where the generated bytes will be written
	 */
	void (*get_bytes) (prf_plus_t *this, size_t length, u_int8_t *buffer);
	
	/**
	 * @brief Allocate pseudo random bytes.
	 * 
	 * Get the next few bytes of the prf+ output. This function
	 * will allocate the required space.
	 * 
	 * @param this			calling object
	 * @param length		number of bytes to get
	 * @param[out] chunk	chunk which will hold generated bytes
	 */
	void (*allocate_bytes) (prf_plus_t *this, size_t length, chunk_t *chunk);
	
	/**
	 * @brief Destroys a prf_plus_t object.
	 *
	 * @param this 			calling object
	 */
	void (*destroy) (prf_plus_t *this);
};

/**
 * @brief Creates a new prf_plus_t object.
 * 
 * Seed will be cloned. prf will
 * not be cloned, must be destroyed outside after
 * prf_plus_t usage.
 * 
 * @param prf				prf object to use
 * @param seed				input seed for prf
 * @return					prf_plus_t object
 * 
 * @ingroup transforms
 */
prf_plus_t *prf_plus_create(prf_t *prf, chunk_t seed);

#endif /*PRF_PLUS_H_*/