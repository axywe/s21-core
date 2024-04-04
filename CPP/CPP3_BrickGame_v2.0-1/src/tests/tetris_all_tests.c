#include <check.h>

#include "../brick_game/tetris/tetris.h"

static GameInfo_t gameInfo;
static BlockInfo_t blockInfo;

START_TEST(test_initializeGame) {
  initializeGame();
  gameInfo = updateCurrentState();
  ck_assert_int_eq(gameInfo.level, 1);
  ck_assert_int_eq(gameInfo.score, 0);
  ck_assert_int_ge(gameInfo.high_score, 0);
  ck_assert_int_eq(gameInfo.speed, 100);
  ck_assert_ptr_nonnull(gameInfo.field);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(gameInfo.field[i][j], 0);
    }
  }
  finalizeGame();
}
END_TEST

START_TEST(test_checkCollision) {
  initializeGame();
  gameInfo = updateCurrentState();
  ck_assert(checkCollision(-1, 0));
  ck_assert(checkCollision(FIELD_WIDTH, 0));
  ck_assert(!checkCollision(FIELD_WIDTH / 2, 0));
  finalizeGame();
}
END_TEST

START_TEST(test_removeCompleteLines) {
  initializeGame();
  gameInfo = updateCurrentState();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    gameInfo.field[FIELD_HEIGHT - 1][x] = 1;
  }
  removeCompleteLines();
  rotateBlock();
  mergeBlockToField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    ck_assert_int_eq(gameInfo.field[FIELD_HEIGHT - 1][x], 0);
  }
  finalizeGame();
}
END_TEST

START_TEST(test_userInput) {
  initializeGame();
  gameInfo = updateCurrentState();
  blockInfo = getBlockInfo();
  ck_assert_int_eq(blockInfo.currentX, 3);
  userInput(Left, false);
  blockInfo = getBlockInfo();
  ck_assert_int_eq(blockInfo.currentX, 2);
  userInput(Right, false);
  blockInfo = getBlockInfo();
  ck_assert_int_eq(blockInfo.currentX, 3);
  userInput(Down, true);
  blockInfo = getBlockInfo();
  ck_assert_int_eq(blockInfo.currentY, 3);
  userInput(Down, false);
  blockInfo = getBlockInfo();
  ck_assert_int_eq(blockInfo.currentY, 4);
  userInput(Terminate, false);
}
END_TEST

START_TEST(test_scoreUpdate) {
  initializeGame();
  gameInfo = updateCurrentState();
  removeCompleteLines();
  ck_assert_int_eq(gameInfo.score, 0);

  for (int x = 0; x < FIELD_WIDTH; x++) {
    gameInfo.field[FIELD_HEIGHT - 1][x] = 1;
  }
  removeCompleteLines();
  gameInfo = updateCurrentState();
  ck_assert_int_eq(gameInfo.score, 100);

  for (int i = 1; i < 5; i++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      gameInfo.field[FIELD_HEIGHT - i][x] = 1;
    }
  }
  removeCompleteLines();
  gameInfo = updateCurrentState();
  ck_assert_int_eq(gameInfo.score, 1600);
  finalizeGame();
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");

  tc_core = tcase_create("Core");
  tcase_set_timeout(tc_core, 1);

  tcase_add_test(tc_core, test_initializeGame);
  tcase_add_test(tc_core, test_checkCollision);
  tcase_add_test(tc_core, test_removeCompleteLines);
  tcase_add_test(tc_core, test_userInput);
  tcase_add_test(tc_core, test_scoreUpdate);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = tetris_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
