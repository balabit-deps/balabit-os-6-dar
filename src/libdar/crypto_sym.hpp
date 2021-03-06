//*********************************************************************/
// dar - disk archive - a backup/restoration program
// Copyright (C) 2002-2052 Denis Corbin
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// to contact the author : http://dar.linux.free.fr/email.html
/*********************************************************************/

    /// \file crypto.hpp
    /// \brief the crypto algoritm definition
    /// \ingroup Private

#ifndef CRYPTO_SYM_HPP
#define CRYPTO_SYM_HPP

extern "C"
{
#if HAVE_GCRYPT_H
#ifndef GCRYPT_NO_DEPRECATED
#define GCRYPT_NO_DEPRECATED
#endif
#include <gcrypt.h>
#endif
}

#include "../my_config.h"
#include <string>

#include "tronconneuse.hpp"
#include "secu_string.hpp"
#include "crypto.hpp"

namespace libdar
{

	/// \ingroup Private
	/// @}

    inline bool crypto_min_ver_libgcrypt_no_bug()
    {
#if CRYPTO_AVAILABLE
	return gcry_check_version(MIN_VERSION_GCRYPT_HASH_BUG);
#else
	return true;
#endif
    }

	/// inherited class from tronconneuse class
	/// \ingroup Private
    class crypto_sym : public tronconneuse
    {
    public:
	crypto_sym(U_32 block_size,
		   const secu_string & password,
		   generic_file & encrypted_side,
		   bool no_initial_shift,
		   const archive_version & reading_ver,
		   crypto_algo algo,
		   bool use_pkcs5);     //< must be set to true when password is human defined, false when password is randomly generated by pseudo-random generator and has the maximum length for the given algorithm
	~crypto_sym() { detruit(); };

	    /// returns the max key length in octets for the given algorithm
	static size_t max_key_len(crypto_algo algo);

	    /// returns the max key length in octets to use to compute a key from a user provided password
	static size_t max_key_len_libdar(crypto_algo algo);

	    /// check whether the given password is reported as strong in regard to the given cipher
	static bool is_a_strong_password(crypto_algo algo, const secu_string & password);

    protected:
	U_32 encrypted_block_size_for(U_32 clear_block_size);
	U_32 clear_block_allocated_size_for(U_32 clear_block_size);
	U_32 encrypt_data(const infinint & block_num,
			  const char *clear_buf, const U_32 clear_size, const U_32 clear_allocated,
			  char *crypt_buf, U_32 crypt_size);
	U_32 decrypt_data(const infinint & block_num,
			  const char *crypt_buf, const U_32 crypt_size,
			  char *clear_buf, U_32 clear_size);

    private:
#if CRYPTO_AVAILABLE
	gcry_cipher_hd_t clef;       //< used to encrypt/decrypt the data
	gcry_cipher_hd_t essiv_clef; //< used to build the Initialization Vector
#endif
	size_t algo_block_size;         //< the block size of the algorithm (main key)
	unsigned char *ivec;            //< algo_block_size allocated in secure memory to be used as Initial Vector
	U_I algo_id;                    //< algo ID in libgcrypt

	void detruit();

	    /// creates a blowfish key using as key a SHA1 of the given string (no IV assigned)
	    ///
	    /// \note such key is intended to be used to generate IV for the main key

#if CRYPTO_AVAILABLE
	static void dar_set_essiv(const secu_string & key,       //< the key to base the essiv on
				  gcry_cipher_hd_t & IVkey,      //< assign essiv from the given (hash) string
				  const archive_version & ver,   //< archive format we read or write
				  crypto_algo main_cipher);      //< the choice of the algo for essiv depends on the cipher used for the main key
	    /// Fills up a new initial vector based on a reference and and a encryption key
	    ///
	    /// \param[in] ref is the reference to base the IV on
	    /// \param[in] ivec is the address where to drop down the new IV
	    /// \param[in] size is the amount of data allocated at ivec address
	    /// \param[in] IVkey is the key used to generate the IV data
	    /// \note the IV is created by encrypting a hash of ref with IVkey
	static void make_ivec(const infinint & ref,
			      unsigned char *ivec,
			      U_I size,
			      const gcry_cipher_hd_t & IVkey);

	    /// Create a hash string of requested length from a given password and interation cout
	static secu_string pkcs5_pass2key(const secu_string & password,         //< human provided password
					  const std::string & salt,             //< salt string
					  U_I iteration_count,                  //< number of time to shake the melange
					  U_I output_length);                   //< length of the string to return

	    /// converts libdar crypto algo designation to index used by libgcrypt
	static U_I get_algo_id(crypto_algo algo);
#endif

#ifdef LIBDAR_NO_OPTIMIZATION
	static void self_test(void);
#endif
    };

	/// @}

} // end of namespace

#endif
