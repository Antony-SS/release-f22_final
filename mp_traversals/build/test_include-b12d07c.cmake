if(EXISTS "/workspaces/CS225/release-f22_final/mp_traversals/build/test_tests-b12d07c.cmake")
  include("/workspaces/CS225/release-f22_final/mp_traversals/build/test_tests-b12d07c.cmake")
else()
  add_test(test_NOT_BUILT-b12d07c test_NOT_BUILT-b12d07c)
endif()
