/*
 *   Copyright (C) 2015,2016,2025 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "QR1676.h"
#include "Log.h"

#include <cstdio>
#include <cassert>

const unsigned int ENCODING_TABLE_1676[] =
	{0x0000U, 0x0273U, 0x04E5U, 0x0696U, 0x09C9U, 0x0BBAU, 0x0D2CU, 0x0F5FU, 0x11E2U, 0x1391U, 0x1507U, 0x1774U,
	 0x182BU, 0x1A58U, 0x1CCEU, 0x1EBDU, 0x21B7U, 0x23C4U, 0x2552U, 0x2721U, 0x287EU, 0x2A0DU, 0x2C9BU, 0x2EE8U,
	 0x3055U, 0x3226U, 0x34B0U, 0x36C3U, 0x399CU, 0x3BEFU, 0x3D79U, 0x3F0AU, 0x411EU, 0x436DU, 0x45FBU, 0x4788U,
	 0x48D7U, 0x4AA4U, 0x4C32U, 0x4E41U, 0x50FCU, 0x528FU, 0x5419U, 0x566AU, 0x5935U, 0x5B46U, 0x5DD0U, 0x5FA3U,
	 0x60A9U, 0x62DAU, 0x644CU, 0x663FU, 0x6960U, 0x6B13U, 0x6D85U, 0x6FF6U, 0x714BU, 0x7338U, 0x75AEU, 0x77DDU,
	 0x7882U, 0x7AF1U, 0x7C67U, 0x7E14U, 0x804FU, 0x823CU, 0x84AAU, 0x86D9U, 0x8986U, 0x8BF5U, 0x8D63U, 0x8F10U,
	 0x91ADU, 0x93DEU, 0x9548U, 0x973BU, 0x9864U, 0x9A17U, 0x9C81U, 0x9EF2U, 0xA1F8U, 0xA38BU, 0xA51DU, 0xA76EU,
	 0xA831U, 0xAA42U, 0xACD4U, 0xAEA7U, 0xB01AU, 0xB269U, 0xB4FFU, 0xB68CU, 0xB9D3U, 0xBBA0U, 0xBD36U, 0xBF45U,
	 0xC151U, 0xC322U, 0xC5B4U, 0xC7C7U, 0xC898U, 0xCAEBU, 0xCC7DU, 0xCE0EU, 0xD0B3U, 0xD2C0U, 0xD456U, 0xD625U,
	 0xD97AU, 0xDB09U, 0xDD9FU, 0xDFECU, 0xE0E6U, 0xE295U, 0xE403U, 0xE670U, 0xE92FU, 0xEB5CU, 0xEDCAU, 0xEFB9U,
	 0xF104U, 0xF377U, 0xF5E1U, 0xF792U, 0xF8CDU, 0xFABEU, 0xFC28U, 0xFE5BU};

const unsigned int DECODING_TABLE_1576[] =
	{0x0000U, 0x0001U, 0x0002U, 0x0003U, 0x0004U, 0x0005U, 0x0006U, 0x4020U, 0x0008U, 0x0009U, 0x000AU, 0x000BU, 
	 0x000CU, 0x000DU, 0x2081U, 0x2080U, 0x0010U, 0x0011U, 0x0012U, 0x0013U, 0x0014U, 0x0C00U, 0x0016U, 0x0C02U, 
	 0x0018U, 0x0120U, 0x001AU, 0x0122U, 0x4102U, 0x0124U, 0x4100U, 0x4101U, 0x0020U, 0x0021U, 0x0022U, 0x4004U, 
	 0x0024U, 0x4002U, 0x4001U, 0x4000U, 0x0028U, 0x0110U, 0x1800U, 0x1801U, 0x002CU, 0x400AU, 0x4009U, 0x4008U, 
	 0x0030U, 0x0108U, 0x0240U, 0x0241U, 0x0034U, 0x4012U, 0x4011U, 0x4010U, 0x0101U, 0x0100U, 0x0103U, 0x0102U, 
	 0x0105U, 0x0104U, 0x1401U, 0x1400U, 0x0040U, 0x0041U, 0x0042U, 0x0043U, 0x0044U, 0x0045U, 0x0046U, 0x4060U, 
	 0x0048U, 0x0049U, 0x0301U, 0x0300U, 0x004CU, 0x1600U, 0x0305U, 0x0304U, 0x0050U, 0x0051U, 0x0220U, 0x0221U, 
	 0x3000U, 0x4200U, 0x3002U, 0x4202U, 0x0058U, 0x1082U, 0x1081U, 0x1080U, 0x3008U, 0x4208U, 0x2820U, 0x1084U, 
	 0x0060U, 0x0061U, 0x0210U, 0x0211U, 0x0480U, 0x0481U, 0x4041U, 0x4040U, 0x0068U, 0x2402U, 0x2401U, 0x2400U, 
	 0x0488U, 0x3100U, 0x2810U, 0x2404U, 0x0202U, 0x0880U, 0x0200U, 0x0201U, 0x0206U, 0x0884U, 0x0204U, 0x0205U, 
	 0x0141U, 0x0140U, 0x0208U, 0x0209U, 0x2802U, 0x0144U, 0x2800U, 0x2801U, 0x0080U, 0x0081U, 0x0082U, 0x0A00U, 
	 0x0084U, 0x0085U, 0x2009U, 0x2008U, 0x0088U, 0x0089U, 0x2005U, 0x2004U, 0x2003U, 0x2002U, 0x2001U, 0x2000U, 
	 0x0090U, 0x0091U, 0x0092U, 0x1048U, 0x0602U, 0x0C80U, 0x0600U, 0x0601U, 0x0098U, 0x1042U, 0x1041U, 0x1040U, 
	 0x2013U, 0x2012U, 0x2011U, 0x2010U, 0x00A0U, 0x00A1U, 0x00A2U, 0x4084U, 0x0440U, 0x0441U, 0x4081U, 0x4080U, 
	 0x6000U, 0x1200U, 0x6002U, 0x1202U, 0x6004U, 0x2022U, 0x2021U, 0x2020U, 0x0841U, 0x0840U, 0x2104U, 0x0842U, 
	 0x2102U, 0x0844U, 0x2100U, 0x2101U, 0x0181U, 0x0180U, 0x0B00U, 0x0182U, 0x5040U, 0x0184U, 0x2108U, 0x2030U, 
	 0x00C0U, 0x00C1U, 0x4401U, 0x4400U, 0x0420U, 0x0421U, 0x0422U, 0x4404U, 0x0900U, 0x0901U, 0x1011U, 0x1010U, 
	 0x0904U, 0x2042U, 0x2041U, 0x2040U, 0x0821U, 0x0820U, 0x1009U, 0x1008U, 0x4802U, 0x0824U, 0x4800U, 0x4801U, 
	 0x1003U, 0x1002U, 0x1001U, 0x1000U, 0x0501U, 0x0500U, 0x1005U, 0x1004U, 0x0404U, 0x0810U, 0x1100U, 0x1101U, 
	 0x0400U, 0x0401U, 0x0402U, 0x0403U, 0x040CU, 0x0818U, 0x1108U, 0x1030U, 0x0408U, 0x0409U, 0x040AU, 0x2060U, 
	 0x0801U, 0x0800U, 0x0280U, 0x0802U, 0x0410U, 0x0804U, 0x0412U, 0x0806U, 0x0809U, 0x0808U, 0x1021U, 0x1020U, 
	 0x5000U, 0x2200U, 0x5002U, 0x2202U};

#define X14             0x00004000   /* vector representation of X^{14} */
#define X8              0x00000100   /* vector representation of X^{8} */
#define MASK7           0xffffff00   /* auxiliary vector for testing */
#define GENPOL          0x00000139   /* generator polinomial, g(x) */

unsigned int CQR1676::getSyndrome1576(unsigned int pattern)
/*
 * Compute the syndrome corresponding to the given pattern, i.e., the
 * remainder after dividing the pattern (when considering it as the vector
 * representation of a polynomial) by the generator polynomial, GENPOL.
 * In the program this pattern has several meanings: (1) pattern = infomation
 * bits, when constructing the encoding table; (2) pattern = error pattern,
 * when constructing the decoding table; and (3) pattern = received vector, to
 * obtain its syndrome in decoding.
 */
{
	unsigned int aux = X14;
 
	if (pattern >= X8) {
		while (pattern & MASK7) {
			while (!(aux & pattern))
				aux = aux >> 1;

			pattern ^= (aux / X8) * GENPOL;
		}
	}

	return pattern;
}

// Compute the EMB against a precomputed list of correct words
void CQR1676::encode(unsigned char* data)
{
	assert(data != nullptr);

	unsigned int value = (data[0U] >> 1) & 0x7FU;
	unsigned int cksum = ENCODING_TABLE_1676[value];

	data[0U] = cksum >> 8;
	data[1U] = cksum & 0xFFU;
}

unsigned char CQR1676::decode(const unsigned char* data)
{
	assert(data != nullptr);

	unsigned int code = (data[0U] << 7) + (data[1U] >> 1);
	unsigned int syndrome = getSyndrome1576(code);
	unsigned int error_pattern = DECODING_TABLE_1576[syndrome];

	code ^= error_pattern;

	return code >> 7;
}
