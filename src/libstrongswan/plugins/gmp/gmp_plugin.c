/*
 * Copyright (C) 2008-2009 Martin Willi
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

#include "gmp_plugin.h"

#include <library.h>
#include "gmp_diffie_hellman.h"
#include "gmp_rsa_private_key.h"
#include "gmp_rsa_public_key.h"

static const char *plugin_name = "gmp";

typedef struct private_gmp_plugin_t private_gmp_plugin_t;

/**
 * private data of gmp_plugin
 */
struct private_gmp_plugin_t {

	/**
	 * public functions
	 */
	gmp_plugin_t public;
};

METHOD(plugin_t, destroy, void,
	private_gmp_plugin_t *this)
{
	lib->crypto->remove_dh(lib->crypto,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->remove_dh(lib->crypto,
						(dh_constructor_t)gmp_diffie_hellman_create_custom);
	lib->creds->remove_builder(lib->creds,
						(builder_function_t)gmp_rsa_private_key_gen);
	lib->creds->remove_builder(lib->creds,
						(builder_function_t)gmp_rsa_private_key_load);
	lib->creds->remove_builder(lib->creds,
						(builder_function_t)gmp_rsa_public_key_load);
	free(this);
}

/*
 * see header file
 */
plugin_t *gmp_plugin_create()
{
	private_gmp_plugin_t *this;

	INIT(this,
		.public = {
			.plugin = {
				.destroy = _destroy,
			},
		},
	);

	lib->crypto->add_dh(lib->crypto, MODP_2048_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_2048_224, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_2048_256, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_1536_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_3072_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_4096_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_6144_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_8192_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_1024_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_1024_160, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);
	lib->crypto->add_dh(lib->crypto, MODP_768_BIT, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create);

	lib->crypto->add_dh(lib->crypto, MODP_CUSTOM, plugin_name,
						(dh_constructor_t)gmp_diffie_hellman_create_custom);

	lib->creds->add_builder(lib->creds, CRED_PRIVATE_KEY, KEY_RSA, FALSE,
						(builder_function_t)gmp_rsa_private_key_gen);
	lib->creds->add_builder(lib->creds, CRED_PRIVATE_KEY, KEY_RSA, TRUE,
						(builder_function_t)gmp_rsa_private_key_load);
	lib->creds->add_builder(lib->creds, CRED_PUBLIC_KEY, KEY_RSA, TRUE,
						(builder_function_t)gmp_rsa_public_key_load);

	return &this->public.plugin;
}

