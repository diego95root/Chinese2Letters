#include <string.h>
#include <stdlib.h>
#include "unity.h"
#include "database.h"
#include "parser.h"

void test_CountOfFilesWithNStrokes(){
    Database * files = openDB("../chars3/");
    int arr[] = {1, 9, 23, 34, 37, 50, 34, 35, 29, 16, 12, 10, 7, 1, 2};
    for (int i = 1; i < 16; i++){
        TEST_ASSERT_EQUAL_INT(arr[i-1], getNumberByStroke(i, files));
    }
    closeDB(files);
}

void test_filenamesByStrokeNumber(){ // on ../chars works better cause they're sorted, only name changes 
    Database * files = openDB("../chars3/");
    char * filenames[][50] = {{"e4b880_01.png"},
    {"e4ba86_02.png", "e4ba8c_02.png", "e4baba_02.png", "e584bf_02.png", "e585a5_02.png", "e587a0_02.png", "e58a9b_02.png", "e58d81_02.png", "e58f88_02.png"},
    {"e4b889_03.png", "e4b88a_03.png", "e4b88b_03.png", "e4b88e_03.png", "e4b8aa_03.png", "e4b988_03.png", "e4b989_03.png", "e4b98b_03.png", "e4b99f_03.png", "e4ba8e_03.png", "e58f8a_03.png", "e58fa3_03.png", "e5a4a7_03.png", "e5a5b3_03.png", "e5ad90_03.png", "e5b08f_03.png", "e5b1b1_03.png", "e5b7a5_03.png", "e5b7b1_03.png", "e5b7b2_03.png", "e6898d_03.png", "e997a8_03.png", "e9a9ac_03.png"},
    {"e4b88d_04.png", "e4b8ad_04.png", "e4b8ba_04.png", "e4b9a6_04.png", "e4ba94_04.png", "e4bb80_04.png", "e4bb8e_04.png", "e4bba5_04.png", "e585ac_04.png", "e58685_04.png", "e58886_04.png", "e58c96_04.png", "e58cba_04.png", "e58f8d_04.png", "e5a4a9_04.png", "e5a4aa_04.png", "e5b091_04.png", "e5bc80_04.png", "e5bf83_04.png", "e6898b_04.png", "e69687_04.png", "e696b9_04.png", "e697a0_04.png", "e697a5_04.png", "e69c88_04.png", "e6af94_04.png", "e6b094_04.png", "e6b0b4_04.png", "e78e8b_04.png", "e8a781_04.png", "e8aea1_04.png", "e8aea4_04.png", "e995bf_04.png", "e9989f_04.png"},
    {"e4b894_05.png", "e4b896_05.png", "e4b89a_05.png", "e4b89c_05.png", "e4b8bb_05.png", "e4bb96_05.png", "e4bba3_05.png", "e4bbac_05.png", "e587ba_05.png", "e58aa0_05.png", "e58aa1_05.png", "e58ebb_05.png", "e58f91_05.png", "e58faa_05.png", "e58faf_05.png", "e58fb8_05.png", "e59b9b_05.png", "e5a484_05.png", "e5a496_05.png", "e5a4b4_05.png", "e5ae83_05.png", "e5afb9_05.png", "e5b094_05.png", "e5b882_05.png", "e5b9b3_05.png", "e5bf85_05.png", "e68993_05.png", "e69cac_05.png", "e6ada3_05.png", "e6b091_05.png", "e7949f_05.png", "e794a8_05.png", "e794b1_05.png", "e794b5_05.png", "e799bd_05.png", "e79bae_05.png", "e7ab8b_05.png"},
    {"e4baa7_06.png", "e4bbb6_06.png", "e4bbbb_06.png", "e4bc9a_06.png", "e58588_06.png", "e58589_06.png", "e585a8_06.png", "e585b3_06.png", "e5868d_06.png", "e5869b_06.png", "e586b3_06.png", "e58899_06.png", "e58aa8_06.png", "e59084_06.png", "e59088_06.png", "e5908c_06.png", "e5908d_06.png", "e5908e_06.png", "e59091_06.png", "e59b9e_06.png", "e59ba0_06.png", "e59ca8_06.png", "e59cb0_06.png", "e59cba_06.png", "e5a49a_06.png", "e5a5b9_06.png", "e5a5bd_06.png", "e5a682_06.png", "e5ae89_06.png", "e5b9b4_06.png", "e5b9b6_06.png", "e5bd93_06.png", "e68890_06.png", "e69c89_06.png", "e69cba_06.png", "e69d83_06.png", "e6aca1_06.png", "e6ada4_06.png", "e88081_06.png", "e8808c_06.png", "e887aa_06.png", "e887b3_06.png", "e8a18c_06.png", "e8a5bf_06.png", "e8aeb8_06.png", "e8aeba_06.png", "e8bebe_06.png", "e8bf87_06.png", "e982a3_06.png", "e997ae_06.png"},
    {"e4b8a4_07.png", "e4bd86_07.png", "e4bd8d_07.png", "e4bd93_07.png", "e4bd95_07.png", "e4bd9c_07.png", "e4bda0_07.png", "e5858b_07.png", "e588a9_07.png", "e588ab_07.png", "e58db3_07.png", "e58db4_07.png", "e590ac_07.png", "e59198_07.png", "e5a3b0_07.png", "e5ba94_07.png", "e5bda2_07.png", "e68891_07.png", "e68a8a_07.png", "e68aa5_07.png", "e697b6_07.png", "e69bb4_07.png", "e69da1_07.png", "e69da5_07.png", "e6b2a1_07.png", "e7a4be_07.png", "e7b3bb_07.png", "e8b5b0_07.png", "e8baab_07.png", "e8bf98_07.png", "e8bf99_07.png", "e8bf9b_07.png", "e9878c_07.png", "e997b4_07.png"},
    {"e4ba8b_08.png", "e4ba9b_08.png", "e4bdbf_08.png", "e585b6_08.png", "e588b0_08.png", "e588b6_08.png", "e58f97_08.png", "e58f98_08.png", "e591bd_08.png", "e5928c_08.png", "e59bbd_08.png", "e5ada6_08.png", "e5ae9a_08.png", "e5ae9e_08.png", "e5bbba_08.png", "e680a7_08.png", "e68896_08.png", "e68980_08.png", "e694be_08.png", "e6988e_08.png", "e69e9c_08.png", "e6b2bb_08.png", "e6b395_08.png", "e789a9_08.png", "e78eb0_08.png", "e79a84_08.png", "e79bb4_08.png", "e79fa5_08.png", "e7a9ba_08.png", "e7bb8f_08.png", "e88085_08.png", "e8a1a8_08.png", "e8af9d_08.png", "e98791_08.png", "e99d9e_08.png"},
    {"e4bebf_09.png", "e4bf9d_09.png", "e4bfa1_09.png", "e5898d_09.png", "e5b086_09.png", "e5baa6_09.png", "e5be88_09.png", "e6809d_09.png", "e680bb_09.png", "e68898_09.png", "e68c87_09.png", "e694bf_09.png", "e698af_09.png", "e6b4bb_09.png", "e782b9_09.png", "e7958c_09.png", "e79bb8_09.png", "e79c8b_09.png", "e7a59e_09.png", "e7a78d_09.png", "e7a791_09.png", "e7bb93_09.png", "e7bb99_09.png", "e7bb9f_09.png", "e7be8e_09.png", "e8a681_09.png", "e8afb4_09.png", "e9878d_09.png", "e99da2_09.png"},
    {"e58e9f_10.png", "e5aeb6_10.png", "e5b195_10.png", "e6a0b7_10.png", "e6b5b7_10.png", "e789b9_10.png", "e79c9f_10.png", "e883bd_10.png", "e8a2ab_10.png", "e8b584_10.png", "e8b5b7_10.png", "e9809a_10.png", "e983a8_10.png", "e983bd_10.png", "e99abe_10.png", "e9ab98_10.png"},
    {"e5819a_11.png", "e59fba_11.png", "e5b8b8_11.png", "e5be97_11.png", "e68385_11.png", "e68ea5_11.png", "e69599_11.png", "e79086_11.png", "e79cbc_11.png", "e79d80_11.png", "e7acac_11.png", "e8b1a1_11.png"},
    {"e5b0b1_12.png", "e5bcba_12.png", "e68f90_12.png", "e696af_12.png", "e69c80_12.png", "e69c9f_12.png", "e784b6_12.png", "e7ad89_12.png", "e98193_12.png", "e9878f_12.png"},
    {"e5838f_13.png", "e683b3_13.png", "e6848f_13.png", "e6849f_13.png", "e695b0_13.png", "e696b0_13.png", "e8a7a3_13.png"},
    {"e7aea1_14.png"},
    {"e5beb7_15.png", "e9a298_15.png"}};

    int len[] = {1, 9, 23, 34, 37, 50, 34, 35, 29, 16, 12, 10, 7, 1, 2};

    for (int i = 0; i < 15; i++){ // for each number of strokes

        char ** strokeFiles = getStrokeFiles(i+1, files);
        
        for (int x = 0; x < len[i]; x++){ // for each character in that group
            
            for (int n = 0; n < len[i]; n++){ // arrays not sorted, so check if there is an element that is equal
                
                if (strcmp(filenames[i][x], strokeFiles[n]) == 0){
                    
                    TEST_ASSERT_EQUAL_STRING(filenames[i][x], strokeFiles[n]);

                    break;
                }
            }

        }

    }

    closeDB(files);
}

/*

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

*/

void test_ScoresSortedCorrectly(){
    Database * files = openDB("../chars3/");
    double arr[][15] = {
    {1, 9, 23, 34, 37, 50, 34, 35, 29, 16, 12, 10, 7, 1, 2},
    {50, 37, 35, 34, 34, 29, 23, 16, 12, 10, 9, 7, 2, 1, 1},
    {1.01, 9.872, 23.7, 34.2, 37.6, 50.1, 34.3, 35.444, 29.2, 16.1, 12.6, 10.89, 7.99, 1, 2},
    {50.1, 37.6, 35.444, 34.3, 34.2, 29.2, 23.7, 16.1, 12.6, 10.89, 9.872, 7.99, 2, 1.01, 1},
    {0.01, 0.872, 0.7, 0.2, 0.6, 0.134, 0.3, 0.444, 0.2, 0.1, 0.69, 0.89, 0.99, 0.1, 0.23},
    {0.99, 0.89, 0.872, 0.7, 0.69, 0.6, 0.444, 0.3, 0.23, 0.2, 0.2, 0.134, 0.1, 0.1, 0.01}};
    for (int i = 0; i < 2; i+=2){
        sortListTest(arr[i], 15);
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(arr[i+1], arr[i], 15);
    }
    closeDB(files);
}

void test_comparisonReturnsCharacter(){
    char * arr[] = {"e4bda0_07.png",  // `ni` character with a stroke that is not joint correctly (islands + 1)
                    "e68891_07.png",  // `wo` written incorrectly, with bad strokes 
                    "e69687_04.png",  
                    "e69c9f_12.png",  
                    "e794a8_05.png",
                    "e5b0b1_12.png",  
                    "e68898_09.png",  
                    "e69c89_06.png",  
                    "e7949f_05.png",  
                    "e997ae_06.png"};
    
    size_t length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < length; i++){

        char wholename[40] = "../test/dataImages/data-";
        strcat(wholename, arr[i]);

        int matrix[500][500];
        readMatrix(wholename, matrix, 500, 500);

        char name[20]; // need to copy the constant string out from RO memory
        strcpy(name, arr[i]);

        char ** splitted = splitFilename(name); // obtain number of strokes for comparison
        int strokes = atoi(splitted[1]);
        free(splitted[0]);
        free(splitted[1]);
        free(splitted);

        charScoreList * results = parserInit(strokes, matrix);
        
        printf("whole: %s, normal: %s, results: ", wholename, arr[i]);

        for (int j = 0; j < results->count; j++){
            if (strcmp(results->elements[j].name, arr[i]) == 0){
                printf("%d out of %d\n", j, results->count);
                break;
            }
        }

        freeCharScoreList(results);

    }

    parserEnd();
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_CountOfFilesWithNStrokes);
    RUN_TEST(test_filenamesByStrokeNumber);
    RUN_TEST(test_ScoresSortedCorrectly);
    RUN_TEST(test_comparisonReturnsCharacter);

    /*
    // TEST FOR READ AND WRITE

    int pixels[500][500];
    char file[] = "e69687_04.png";

    readMatrix(file, pixels, 500, 500);
    writeMatrix(pixels, 500, 500);
    */

    return UNITY_END();
}