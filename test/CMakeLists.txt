# ==========================
# Test Configuration
# ==========================
# Collect all test source files (explicit glob to avoid hidden files)
file(GLOB NMR_TEST_FILES 
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
     LIST_DIRECTORIES false)

# Link test executable to core library and include paths
foreach(TEST_FILE ${NMR_TEST_FILES})
    # Extract test name (e.g., test_string_utils.cpp -> test_string_utils)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    
    # Skip if no test files found (safety guard)
    if(NOT TEST_FILE)
        continue()
    endif()

    # Create test executable
    add_executable(${TEST_NAME} ${TEST_FILE}
    )

    # Link dependencies (pthread is optional for StringUtils test)
    target_link_libraries(${TEST_NAME}
        PRIVATE
            nmr_lib  # Link to core NativeMapReduce library
    )
    
    # Include paths for tests
    target_include_directories(${TEST_NAME}
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include  # Public API headers
            ${CMAKE_CURRENT_SOURCE_DIR}    # Test-specific headers
    )
    
    # Add test to CTest framework (CRITICAL: REMOVE WORKING_DIRECTORY!)
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
        # ✅ Remove WORKING_DIRECTORY entirely (uses default build directory)
    )
    
    # Set test properties (simplified - no environment vars for StringUtils)
    set_tests_properties(${TEST_NAME}
        PROPERTIES
            TIMEOUT 10  # Fail test if it takes >10 seconds
            # ✅ Remove ENVIRONMENT line (unneeded for StringUtils test)
            # Fix permission issues on macOS/Linux
            RUN_SERIAL ON
    )
endforeach()

# Optional: Create resources directory (if needed for future tests)
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/resources")