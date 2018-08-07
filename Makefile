#==============================================================
#
# Copyright 2018 Los Alamos National Laboratory
# Copyright 2009-2018 The Purdue University and Purdue University
#                     Research Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# =============================================================

CC := g++
SRCDIR := src
BUILDDIR := release
CFLAGS := -std=c++11 -fopenmp -O3
LDFLAGS := -fopenmp 

all: $(BUILDDIR)/jacobi

$(BUILDDIR)/%: $(BUILDDIR)/%.o
		$(CC) $< $(LIBFLAGS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
		@mkdir -p $(BUILDDIR)
		$(CC) -c $(CCFLAGS) $< -o $@

run_jacobi: $(BUILDDIR)/jacobi
		./$(BUILDDIR)/jacobi

clean:
	@echo " Cleaning..."
	@rm -fr $(BUILDDIR) 2>/dev/null || true

.PHONY: clean
	.PRECIOUS: $(BUILDDIR)/%.o
