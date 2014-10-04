#-------------------------------------------------------------------------------
# C++ Brian Chau Helper Library
#
# Copyright (c) Brian Chau, 2014
#
# me@brianchau.ca
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# Author information at http://www.brianchau.ca/
#
# Makefile
#
# Reminder that Makefile must use tabs and not spaces
#-------------------------------------------------------------------------------

CC=g++
CFLAGS=-c -Wall -std=c++11

all: clean run.o
	$(CC) run.o

run.o: run.cpp
	$(CC) $(CFLAGS) run.cpp

clean:
	rm -f a.out run.o
