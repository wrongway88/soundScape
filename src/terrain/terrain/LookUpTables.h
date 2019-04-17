/**
 * Look up tables from "Efficient implementation of Marching Cubes cases with topological guarantees"
 * by Lewiner, Lopes, Vieira and Tavares
 */

#ifndef LOOK_UP_TABLE_H
#define LOOK_UP_TABLE_H

class LookUpTables
{
public:
	static const char m_cases[256][2];

	static const char m_tiling1[16][3];

	static const char m_tiling2[24][6];

	static const char m_test3[24];
	static const char m_tiling3_1[24][6];
	static const char m_tiling3_2[24][12];

	static const char m_test4[8];
	static const char m_tiling4_1[8][6];
	static const char m_tiling4_2[8][18];

	static const char m_tiling5[48][9];

	static const char m_test6[48][3];
	static const char m_tiling6_1_1[48][9];
	static const char m_tiling6_1_2[48][27];
	static const char m_tiling6_2[48][15];

	static const char m_test7[16][5];
	static const char m_tiling7_1[16][9];
	static const char m_tiling7_2[16][3][15];
	static const char m_tiling7_3[16][3][27];
	static const char m_tiling7_4_1[16][15];
	static const char m_tiling7_4_2[16][27];

	static const char m_tiling8[6][6];

	static const char m_tiling9[8][12];

	static const char m_test10[6][3];
	static const char m_tiling10_1_1[6][12];
	static const char m_tiling10_1_1_[6][12];
	static const char m_tiling10_1_2[6][24];
	static const char m_tiling10_2[6][24];
	static const char m_tiling10_2_[6][24];

	static const char m_tiling11[12][12];

	static const char m_test12[24][4];
	static const char m_tiling12_1_1[24][12];
	static const char m_tiling12_1_1_[24][12];
	static const char m_tiling12_1_2[24][24];
	static const char m_tiling12_2[24][24];
	static const char m_tiling12_2_[24][24];

	static const char m_test13[2][7];
	static const char m_subconfig13[64];
	static const char m_tiling13_1[2][12];
	static const char m_tiling13_1_[2][12];
	static const char m_tiling13_2[2][6][18];
	static const char m_tiling13_2_[2][6][18];
	static const char m_tiling13_3[2][12][30];
	static const char m_tiling13_3_[2][12][30];
	static const char m_tiling13_4[2][4][36];
	static const char m_tiling13_5_1[2][4][18];
	static const char m_tiling13_5_2[2][4][30];

	static const char m_tiling14[12][12];
};

#endif