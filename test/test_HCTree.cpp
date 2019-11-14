#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        freqs['b'] = 3;
        freqs['c'] = 3;
        tree.build(freqs);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), 'b');
}

class MyHCTree : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    MyHCTree() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        freqs['b'] = 6;
        freqs['c'] = 8;
        freqs['d'] = 3;
        freqs['e'] = 10;
        freqs['f'] = 20;
        tree.build(freqs);
    }
};

TEST_F(MyHCTree, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "1011");
}

TEST_F(MyHCTree, TEST_DECODE) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), (byte)-1);
}

class MyHCTree2 : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    MyHCTree2() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        tree.build(freqs);
    }
};

TEST_F(MyHCTree2, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "1");
}

TEST_F(MyHCTree2, TEST_DECODE) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), (byte)-1);
}

class MyHCTree3 : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    MyHCTree3() {
        // initialization code here
        vector<unsigned int> freqs(256, 0);
        tree.build(freqs);
    }
};
TEST_F(MyHCTree3, TEST_DECODE) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), (byte)-1);
}

class MyHCTree4 : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    MyHCTree4() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        freqs['b'] = 3;
        freqs['c'] = 3;
        tree.build(freqs);
    }
};

TEST_F(MyHCTree4, TEST_ENCODE) {
    stringstream ss;
    BitOutputStream bos(ss);
    tree.encode('b', bos);
    ASSERT_EQ(ss.get(), 192);
}

TEST_F(MyHCTree4, TEST_DECODE) {
    stringstream ss;
    string s = "11000000";

    string ascii = string(1, stoi(s, nullptr, 2));
    ss.str(ascii);
    BitInputStream inputStream(ss);
    ASSERT_EQ(tree.decode(inputStream), 'b');
}

class MyHCTree5 : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    MyHCTree5() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        freqs['b'] = 6;
        freqs['c'] = 8;
        freqs['d'] = 3;
        freqs['e'] = 10;
        freqs['f'] = 20;
        tree.build(freqs);
    }
};

TEST_F(MyHCTree5, TEST_ENCODE) {
    stringstream ss;
    BitOutputStream bos(ss);
    tree.encode('a', bos);
    ASSERT_EQ(ss.get(), 176);
}

TEST_F(MyHCTree5, TEST_DECODE) {
    istringstream is("166");
    ASSERT_EQ(tree.decode(is), (byte)-1);
}