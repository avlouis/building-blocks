# This file is part of avlouis's building-blocks.
#
# It is licensed under the terms of the University of Illinois/NCSA
# Open Source License.  See the LICENSE file for detailed information
# regarding the copyright and license terms.
#
# SPDX-License-Identifier: NCSA

TEST = ringbuffer

TEST_BINARY = test_$(TEST)
TEST_SOURCE = $(TEST_BINARY).cpp
SOURCE_HEADER = $(TEST).hpp
SOURCE_IMPLEMENTATION = $(TEST).cpp

CATCH_DIR = ../../../third_party/catch
CATCH_HPP = $(CATCH_DIR)/catch.hpp

.PHONY: all test test_valgrind

all: test_valgrind

test: $(TEST_BINARY)
	./$(TEST_BINARY)

test_valgrind: $(TEST_BINARY)
	valgrind --leak-check=full ./$(TEST_BINARY)

$(TEST_BINARY): $(TEST_SOURCE) $(SOURCE_HEADER)		\
		$(SOURCE_IMPLEMENTATION) $(CATCH_HPP)
	g++ -o $@ -I$(CATCH_DIR) $(TEST_SOURCE)
