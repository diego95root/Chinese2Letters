#include "unity.h"
#include "database.h"

void test_CountOfFilesWithNStrokes(){
    Database * files = openDB("../chars/");
    int arr[] = {1, 9, 23, 34, 37, 50, 34, 35, 29, 16, 12, 10, 7, 1, 2};
    for (int i = 1; i < 16; i++){
        TEST_ASSERT_EQUAL_INT(arr[i-1], getNumberByStroke(i, files));
    }
    closeDB(files);
}

void test_filenamesByStrokeNumber(){
    Database * files = openDB("../chars/");
    char * filenames[][50] = {{"4e00_01.png"},
    {"4e86_02.png", "4e8c_02.png", "4eba_02.png", "513f_02.png", "5165_02.png", "51e0_02.png", "529b_02.png", "5341_02.png", "53c8_02.png"},
    {"4e09_03.png", "4e0a_03.png", "4e0b_03.png", "4e0e_03.png", "4e2a_03.png", "4e48_03.png", "4e49_03.png", "4e4b_03.png", "4e5f_03.png", "4e8e_03.png", "53ca_03.png", "53e3_03.png", "5927_03.png", "5973_03.png", "5b50_03.png", "5c0f_03.png", "5c71_03.png", "5de5_03.png", "5df1_03.png", "5df2_03.png", "624d_03.png", "95e8_03.png", "9a6c_03.png"},
    {"4e0d_04.png", "4e2d_04.png", "4e3a_04.png", "4e66_04.png", "4e94_04.png", "4ec0_04.png", "4ece_04.png", "4ee5_04.png", "516c_04.png", "5185_04.png", "5206_04.png", "5316_04.png", "533a_04.png", "53cd_04.png", "5929_04.png", "592a_04.png", "5c11_04.png", "5f00_04.png", "5fc3_04.png", "624b_04.png", "6587_04.png", "65b9_04.png", "65e0_04.png", "65e5_04.png", "6708_04.png", "6bd4_04.png", "6c14_04.png", "6c34_04.png", "738b_04.png", "89c1_04.png", "8ba1_04.png", "8ba4_04.png", "957f_04.png", "961f_04.png"},
    {"4e14_05.png", "4e16_05.png", "4e1a_05.png", "4e1c_05.png", "4e3b_05.png", "4ed6_05.png", "4ee3_05.png", "4eec_05.png", "51fa_05.png", "52a0_05.png", "52a1_05.png", "53bb_05.png", "53d1_05.png", "53ea_05.png", "53ef_05.png", "53f8_05.png", "56db_05.png", "5904_05.png", "5916_05.png", "5934_05.png", "5b83_05.png", "5bf9_05.png", "5c14_05.png", "5e02_05.png", "5e73_05.png", "5fc5_05.png", "6253_05.png", "672c_05.png", "6b63_05.png", "6c11_05.png", "751f_05.png", "7528_05.png", "7531_05.png", "7535_05.png", "767d_05.png", "76ee_05.png", "7acb_05.png"},
    {"4ea7_06.png", "4ef6_06.png", "4efb_06.png", "4f1a_06.png", "5148_06.png", "5149_06.png", "5168_06.png", "5173_06.png", "518d_06.png", "519b_06.png", "51b3_06.png", "5219_06.png", "52a8_06.png", "5404_06.png", "5408_06.png", "540c_06.png", "540d_06.png", "540e_06.png", "5411_06.png", "56de_06.png", "56e0_06.png", "5728_06.png", "5730_06.png", "573a_06.png", "591a_06.png", "5979_06.png", "597d_06.png", "5982_06.png", "5b89_06.png", "5e74_06.png", "5e76_06.png", "5f53_06.png", "6210_06.png", "6709_06.png", "673a_06.png", "6743_06.png", "6b21_06.png", "6b64_06.png", "8001_06.png", "800c_06.png", "81ea_06.png", "81f3_06.png", "884c_06.png", "897f_06.png", "8bb8_06.png", "8bba_06.png", "8fbe_06.png", "8fc7_06.png", "90a3_06.png", "95ee_06.png"},
    {"4e24_07.png", "4f46_07.png", "4f4d_07.png", "4f53_07.png", "4f55_07.png", "4f5c_07.png", "4f60_07.png", "514b_07.png", "5229_07.png", "522b_07.png", "5373_07.png", "5374_07.png", "542c_07.png", "5458_07.png", "58f0_07.png", "5e94_07.png", "5f62_07.png", "6211_07.png", "628a_07.png", "62a5_07.png", "65f6_07.png", "66f4_07.png", "6761_07.png", "6765_07.png", "6ca1_07.png", "793e_07.png", "7cfb_07.png", "8d70_07.png", "8eab_07.png", "8fd8_07.png", "8fd9_07.png", "8fdb_07.png", "91cc_07.png", "95f4_07.png"},
    {"4e8b_08.png", "4e9b_08.png", "4f7f_08.png", "5176_08.png", "5230_08.png", "5236_08.png", "53d7_08.png", "53d8_08.png", "547d_08.png", "548c_08.png", "56fd_08.png", "5b66_08.png", "5b9a_08.png", "5b9e_08.png", "5efa_08.png", "6027_08.png", "6216_08.png", "6240_08.png", "653e_08.png", "660e_08.png", "679c_08.png", "6cbb_08.png", "6cd5_08.png", "7269_08.png", "73b0_08.png", "7684_08.png", "76f4_08.png", "77e5_08.png", "7a7a_08.png", "7ecf_08.png", "8005_08.png", "8868_08.png", "8bdd_08.png", "91d1_08.png", "975e_08.png"},
    {"4fbf_09.png", "4fdd_09.png", "4fe1_09.png", "524d_09.png", "5c06_09.png", "5ea6_09.png", "5f88_09.png", "601d_09.png", "603b_09.png", "6218_09.png", "6307_09.png", "653f_09.png", "662f_09.png", "6d3b_09.png", "70b9_09.png", "754c_09.png", "76f8_09.png", "770b_09.png", "795e_09.png", "79cd_09.png", "79d1_09.png", "7ed3_09.png", "7ed9_09.png", "7edf_09.png", "7f8e_09.png", "8981_09.png", "8bf4_09.png", "91cd_09.png", "9762_09.png"},
    {"539f_10.png", "5bb6_10.png", "5c55_10.png", "6837_10.png", "6d77_10.png", "7279_10.png", "771f_10.png", "80fd_10.png", "88ab_10.png", "8d44_10.png", "8d77_10.png", "901a_10.png", "90e8_10.png", "90fd_10.png", "96be_10.png", "9ad8_10.png"},
    {"505a_11.png", "57fa_11.png", "5e38_11.png", "5f97_11.png", "60c5_11.png", "63a5_11.png", "6559_11.png", "7406_11.png", "773c_11.png", "7740_11.png", "7b2c_11.png", "8c61_11.png"},
    {"5c31_12.png", "5f3a_12.png", "63d0_12.png", "65af_12.png", "6700_12.png", "671f_12.png", "7136_12.png", "7b49_12.png", "9053_12.png", "91cf_12.png"},
    {"50cf_13.png", "60f3_13.png", "610f_13.png", "611f_13.png", "6570_13.png", "65b0_13.png", "89e3_13.png"},
    {"7ba1_14.png"},
    {"5fb7_15.png", "9898_15.png"}};

    int len[] = {1, 9, 23, 34, 37, 50, 34, 35, 29, 16, 12, 10, 7, 1, 2};

    for (int i = 0; i < 15; i++){

        char ** strokeFiles = getStrokeFiles(i+1, files);
        
        for (int x = 0; x < len[i]; x++){
            
            TEST_ASSERT_EQUAL_STRING(filenames[i][x], strokeFiles[x]);

        }

    }

    closeDB(files);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_CountOfFilesWithNStrokes);
    RUN_TEST(test_filenamesByStrokeNumber);
    return UNITY_END();
}