////
////  main.cpp
////  mini-stl
////
////  Created by cz-mac on 2021/11/2.
////
//#include <gtest/gtest.h>
//#include <string>
//#include "stl_vector.h"
//#include "stl_list.h"
//using namespace ::MiniSTL;
//using std::string;
//
//class VectorTest : public testing::Test {
//protected:
//    virtual void SetUp() {
//        // set pre data
//        vi = {1, 2, 3, 4, 5};
//        vf = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//        vd = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//        vb.resize(5);
//        vs = {"hello", "hello"};
//        vvi = {{1, 2, 3}, {1, 2, 3}};
//    }
//    // pre structure
//    struct BAR {
//        int a;
//        double b;
//    };
//    vector<int> vi;
//    vector<float> vf;
//    vector<double> vd;
//    vector<BAR> vb;
//    vector<string> vs;
//    vector<vector<int>> vvi;
//};
//
//TEST_F(VectorTest, DEFAULT_CTOR) {
//    EXPECT_NO_THROW(vector<int>());
//    EXPECT_NO_THROW(vector<float>());
//    EXPECT_NO_THROW(vector<double>());
//    EXPECT_NO_THROW(vector<string>());
//    EXPECT_NO_THROW(vector<BAR>());
//    EXPECT_NO_THROW(vector<vector<int>>());
//}
//
//TEST_F(VectorTest, CTOR_WITH_SIZE) {
//    EXPECT_NO_THROW(vector<int>(5));
//    EXPECT_NO_THROW(vector<float>(5));
//    EXPECT_NO_THROW(vector<double>(5));
//    EXPECT_NO_THROW(vector<string>(5));
//    EXPECT_NO_THROW(vector<BAR>(5));
//    EXPECT_NO_THROW(vector<vector<int>>(5));
//}
//
//TEST_F(VectorTest, CTOR_WITH_VALUE) {
//    EXPECT_NO_THROW(vector<int>(5, 5));
//    EXPECT_NO_THROW(vector<float>(5, 5.0f));
//    EXPECT_NO_THROW(vector<double>(5, 5.0f));
//    EXPECT_NO_THROW(vector<string>(5, "hello"));
//    EXPECT_NO_THROW(vector<BAR>(5, BAR()));
//    EXPECT_NO_THROW(vector<vector<int>>(5, {1, 2, 3}));
//}
//
//TEST_F(VectorTest, CTOR_WITH_INPUTITERATOR) {
//    EXPECT_NO_THROW(vector<int>(vi.begin(), vi.end()));
//    EXPECT_NO_THROW(vector<int>(vi.cbegin(), vi.cend()));
//    EXPECT_NO_THROW(vector<float>(vf.begin(), vf.end()));
//    EXPECT_NO_THROW(vector<float>(vf.cbegin(), vf.cend()));
//    EXPECT_NO_THROW(vector<double>(vd.begin(), vd.end()));
//    EXPECT_NO_THROW(vector<double>(vd.cbegin(), vd.cend()));
//    EXPECT_NO_THROW(vector<BAR>(vb.begin(), vb.end()));
//    EXPECT_NO_THROW(vector<BAR>(vb.cbegin(), vb.cend()));
//    EXPECT_NO_THROW(vector<vector<int>>(vvi.begin(), vvi.end()));
//    EXPECT_NO_THROW(vector<vector<int>>(vvi.cbegin(), vvi.cend()));
//    // C API
//    int ai[5] = {1, 2, 3, 4, 5};
//    EXPECT_NO_THROW(vector<int>(ai, ai + 5));
//    double ad[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//    EXPECT_NO_THROW(vector<double>(ad, ad + 5));
//    string as[5] = {"a", "b", "c", "d", "f"};
//    EXPECT_NO_THROW(vector<string>(as, as + 5));
//}
//
//TEST_F(VectorTest, CTOR_WITH_INITIAL_LIST) {
//    EXPECT_NO_THROW(vector<int>({1, 2, 3, 4, 5}));
//    EXPECT_NO_THROW(vector<float>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}));
//    EXPECT_NO_THROW(vector<double>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}));
//    EXPECT_NO_THROW(vector<string>({"hello", "world"}));
//    EXPECT_NO_THROW(vector<vector<int>>({{1, 2, 3}, {4, 5, 6}}));
//}
//
//TEST_F(VectorTest, COPY_CTOR) {
//    EXPECT_NO_THROW(vector<int>(vi));
//    EXPECT_NO_THROW(vector<float>(vf));
//    EXPECT_NO_THROW(vector<double>(vd));
//    EXPECT_NO_THROW(vector<string>(vs));
//    EXPECT_NO_THROW(vector<BAR>(vb));
//    EXPECT_NO_THROW(vector<vector<int>>(vvi));
//}
//
//TEST_F(VectorTest, MOVE_CTOR) {
//    EXPECT_NO_THROW(vector<int>(std::move(vi)));
//    EXPECT_NO_THROW(vector<float>(std::move(vf)));
//    EXPECT_NO_THROW(vector<double>(std::move(vd)));
//    EXPECT_NO_THROW(vector<string>(std::move(vs)));
//    EXPECT_NO_THROW(vector<BAR>(std::move(vb)));
//    EXPECT_NO_THROW(vector<vector<int>>(std::move(vvi)));
//}
//
//TEST_F(VectorTest, DTOR) {
//    /*
//    // It is not recommended in C++ to explicitly call the destructor manually.
//    // Because this operation will cause repeated memory release.
//    vector<int> temp_vi = {1,2,3};
//    int* p = &temp_vi[0];
//    temp_vi.~vector();
//    EXPECT_FALSE(*p == 1);
//    */
//    vector<int> *p = new vector<int>(5, 1);
//    int *p2i = &((*p)[0]);
//    EXPECT_EQ(*p2i, 1);
//    delete p;
//    EXPECT_NE(*p2i, 1);
//}
//
//TEST_F(VectorTest, COPYASSIGN_WITH_SELF) {
//    vector<int> temp_vi(5, 2);
//    vi = temp_vi;
//    for (auto i : vi) EXPECT_EQ(i, 2);
//    vector<float> temp_vf(5, 2.0f);
//    vf = temp_vf;
//    for (auto f : vf) EXPECT_EQ(f, 2.0f);
//    vector<double> temp_vd(5, 2.235f);
//    vd = temp_vd;
//    for (auto d : vd) EXPECT_EQ(d, 2.235f);
//    vector<string> temp_vs(5, "hello");
//    vs = temp_vs;
//    for (auto s : vs) EXPECT_EQ(s, "hello");
//    vector<vector<int>> temp_vvi(5, {1, 2, 3});
//    vvi = temp_vvi;
//    for (auto vi : vvi) EXPECT_EQ(vi, vector<int>({1, 2, 3}));
//}
//
//TEST_F(VectorTest, COPYASSIGN_WITH_INITIAL_LIST) {
//    vi = {2, 2, 2, 2, 2};
//    for (auto i : vi) EXPECT_EQ(i, 2);
//    vf = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
//    for (auto f : vf) EXPECT_EQ(f, 2.0f);
//    vd = {2.235f};
//    for (auto d : vd) EXPECT_EQ(d, 2.235f);
//    vs = {"hello", "hello", "hello"};
//    for (auto s : vs) EXPECT_EQ(s, "hello");
//    vvi = {vector<int>({1, 2, 3}), vector<int>({1, 2, 3})};
//    for (auto vi : vvi) EXPECT_EQ(vi, vector<int>({1, 2, 3}));
//}
//
//TEST_F(VectorTest, MOVEASSIGN_WITH_SELF) {
//    vector<int> temp_vi(5, 2);
//    vi = std::move(temp_vi);
//    for (auto i : vi) EXPECT_EQ(i, 2);
//    for (auto i : temp_vi) EXPECT_NE(i, 2);
//    vector<float> temp_vf(5, 2.0f);
//    vf = std::move(temp_vf);
//    for (auto f : vf) EXPECT_EQ(f, 2.0f);
//    for (auto f : temp_vf) EXPECT_NE(f, 2.0f);
//    vector<double> temp_vd(5, 2.235f);
//    vd = std::move(temp_vd);
//    for (auto d : vd) EXPECT_EQ(d, 2.235f);
//    for (auto d : temp_vd) EXPECT_NE(d, 2.235f);
//    vector<string> temp_vs(5, "hello");
//    vs = std::move(temp_vs);
//    for (auto s : vs) EXPECT_EQ(s, "hello");
//    for (auto s : temp_vs) EXPECT_NE(s, "hello");
//    vector<vector<int>> temp_vvi(5, {1, 2, 3});
//    vvi = std::move(temp_vvi);
//    for (auto vi : vvi) EXPECT_EQ(vi, vector<int>({1, 2, 3}));
//    for (auto vi : temp_vvi) EXPECT_NE(vi, vector<int>({1, 2, 3}));
//}
//
//TEST_F(VectorTest, BEGIN_AND_END) {
//    for (auto it = vi.begin(); it != vi.end(); ++it) {
//        EXPECT_EQ(*it, it - vi.begin() + 1);
//        *it = 5;
//    }
//    for (auto it = vi.cbegin(); it != vi.cend(); ++it) EXPECT_EQ(*it, 5);
//    for (auto it = vi.rbegin(); it != vi.rend(); ++it) {
//        EXPECT_EQ(*it, 5);
//        *it = 3;
//    }
//    for (auto it = vi.crbegin(); it != vi.crend(); ++it) {
//        EXPECT_EQ(*it, 3);
//    }
//    for (auto it = vf.begin(); it != vf.end(); ++it) {
//        EXPECT_EQ(*it, it - vf.begin() + 1.0f);
//        *it = 5.0f;
//    }
//    for (auto it = vf.cbegin(); it != vf.cend(); ++it) EXPECT_EQ(*it, 5.0f);
//    for (auto it = vf.rbegin(); it != vf.rend(); ++it) {
//        EXPECT_EQ(*it, 5.0f);
//        *it = 3.0f;
//    }
//    for (auto it = vf.crbegin(); it != vf.crend(); ++it) {
//        EXPECT_EQ(*it, 3.0f);
//    }
//    for (auto it = vd.begin(); it != vd.end(); ++it) {
//        EXPECT_EQ(*it, it - vd.begin() + 1.0f);
//        *it = 5.0f;
//    }
//    for (auto it = vd.cbegin(); it != vd.cend(); ++it) EXPECT_EQ(*it, 5.0f);
//    for (auto it = vd.rbegin(); it != vd.rend(); ++it) {
//        EXPECT_EQ(*it, 5.0f);
//        *it = 3.0f;
//    }
//    for (auto it = vd.crbegin(); it != vd.crend(); ++it) {
//        EXPECT_EQ(*it, 3.0f);
//    }
//    for (auto it = vs.begin(); it != vs.end(); ++it) {
//        EXPECT_EQ(*it, "hello");
//        *it = "world";
//    }
//    for (auto it = vs.cbegin(); it != vs.cend(); ++it) EXPECT_EQ(*it, "world");
//    for (auto it = vs.rbegin(); it != vs.rend(); ++it) {
//        EXPECT_EQ(*it, "world");
//        *it = "hello";
//    }
//    for (auto it = vs.crbegin(); it != vs.crend(); ++it) {
//        EXPECT_EQ(*it, "hello");
//    }
//    for (auto it = vvi.begin(); it != vvi.end(); ++it) {
//        EXPECT_EQ(*it, vector<int>({1, 2, 3}));
//        *it = {4, 5, 6};
//    }
//    for (auto it = vvi.cbegin(); it != vvi.cend(); ++it)
//        EXPECT_EQ(*it, vector<int>({4, 5, 6}));
//    for (auto it = vvi.rbegin(); it != vvi.rend(); ++it) {
//        EXPECT_EQ(*it, vector<int>({4, 5, 6}));
//        *it = {7, 8, 9};
//    }
//    for (auto it = vvi.crbegin(); it != vvi.crend(); ++it) {
//        EXPECT_EQ(*it, vector<int>({7, 8, 9}));
//    }
//}
//
//TEST_F(VectorTest, FRONT_AND_BACK) {
//    EXPECT_EQ(vi.front(), 1);
//    vi.front() = 2;
//    EXPECT_EQ(vi.front(), 2);
//    EXPECT_EQ(vi.back(), 5);
//    vi.back() = 2;
//    EXPECT_EQ(vi.back(), 2);
//    EXPECT_EQ(vf.front(), 1.0f);
//    vf.front() = 2.0f;
//    EXPECT_EQ(vf.front(), 2.0f);
//    EXPECT_EQ(vf.back(), 5.0f);
//    vf.back() = 2.0f;
//    EXPECT_EQ(vf.back(), 2.0f);
//    EXPECT_EQ(vd.front(), 1.0f);
//    vd.front() = 2.0f;
//    EXPECT_EQ(vd.front(), 2.0f);
//    EXPECT_EQ(vd.back(), 5.0f);
//    vd.back() = 2.0f;
//    EXPECT_EQ(vd.back(), 2.0f);
//    EXPECT_EQ(vs.front(), "hello");
//    vs.front() = "world";
//    EXPECT_EQ(vs.front(), "world");
//    EXPECT_EQ(vs.back(), "hello");
//    vs.back() = "world";
//    EXPECT_EQ(vs.back(), "world");
//    EXPECT_EQ(vvi.front(), vector<int>({1, 2, 3}));
//    vvi.front() = {4, 5, 6};
//    EXPECT_EQ(vvi.front(), vector<int>({4, 5, 6}));
//    EXPECT_EQ(vvi.back(), vector<int>({1, 2, 3}));
//    vvi.back() = {4, 5, 6};
//    EXPECT_EQ(vvi.back(), vector<int>({4, 5, 6}));
//}
//
//TEST_F(VectorTest, RANDOMACCESS) {
//    for (size_t i = 0; i != vi.size(); ++i) EXPECT_EQ(vi[i], i + 1);
//    for (size_t i = 0; i != vf.size(); ++i) EXPECT_EQ(vf[i], i + 1.0f);
//    for (size_t i = 0; i != vd.size(); ++i) EXPECT_EQ(vd[i], i + 1.0f);
//    for (size_t i = 0; i != vs.size(); ++i) EXPECT_EQ(vs[i], "hello");
//    for (size_t i = 0; i != vvi.size(); ++i)
//        EXPECT_EQ(vvi[i], vector<int>({1, 2, 3}));
//}
//
//TEST_F(VectorTest, SIZE_AND_CAPACITY) {
//    EXPECT_EQ(vi.size(), 5);
//    EXPECT_EQ(vi.capacity(), 5);
//    vi.resize(3);
//    EXPECT_EQ(vi.size(), 3);
//    EXPECT_EQ(vi.capacity(), 5);
//    vi.resize(10, 5);
//    for (size_t i = 3; i != 10; ++i) EXPECT_EQ(vi[i], 5);
//    EXPECT_EQ(vi.size(), 10);
//    EXPECT_EQ(vi.capacity(), 10);
//    vi.reserve(3);
//    EXPECT_NE(vi.size(), 3);
//    EXPECT_NE(vi.capacity(), 3);
//    vi.reserve(20);
//    EXPECT_EQ(vi.size(), 10);
//    EXPECT_EQ(vi.capacity(), 20);
//    vi.shrink_to_fit();
//    EXPECT_EQ(vi.size(), 10);
//    EXPECT_EQ(vi.size(), vi.capacity());
//}
//
//TEST_F(VectorTest, COMPARATOR) {
//    vector<int> temp_vi = {1, 2, 3, 4, 5};
//    EXPECT_TRUE(temp_vi == vi);
//    EXPECT_FALSE(temp_vi != vi);
//    vector<float> temp_vf(vf);
//    EXPECT_TRUE(temp_vf == vf);
//    EXPECT_FALSE(temp_vf != vf);
//    vector<double> temp_vd(vd.cbegin(), vd.cend());
//    EXPECT_TRUE(temp_vd == vd);
//    EXPECT_FALSE(temp_vd != vd);
//    vector<string> temp_vs(std::move(vs));
//    EXPECT_FALSE(temp_vs == vs);
//    EXPECT_TRUE(temp_vs != vs);
//    vector<vector<int>> temp_vvi({{1, 2, 3}, {1, 2, 3}});
//    EXPECT_TRUE(temp_vvi == vvi);
//    EXPECT_FALSE(temp_vvi != vvi);
//}
//
//TEST_F(VectorTest, PUSH_AND_POP) {
//    vi.push_back(6);
//    EXPECT_EQ(vi.back(), 6);
//    EXPECT_EQ(vi.size(), 6);
//    EXPECT_EQ(vi.capacity(), 10);
//    vi.pop_back();
//    EXPECT_EQ(vi.back(), 5);
//    EXPECT_EQ(vi.size(), 5);
//    EXPECT_EQ(vi.capacity(), 10);
//    vf.push_back(6.0f);
//    EXPECT_EQ(vf.back(), 6.0f);
//    EXPECT_EQ(vf.size(), 6);
//    EXPECT_EQ(vf.capacity(), 10);
//    vf.pop_back();
//    EXPECT_EQ(vf.back(), 5.0f);
//    EXPECT_EQ(vf.size(), 5);
//    EXPECT_EQ(vf.capacity(), 10);
//    vd.push_back(6.0f);
//    EXPECT_EQ(vd.back(), 6.0f);
//    EXPECT_EQ(vd.size(), 6);
//    EXPECT_EQ(vd.capacity(), 10);
//    vd.pop_back();
//    EXPECT_EQ(vd.back(), 5.0f);
//    EXPECT_EQ(vd.size(), 5);
//    EXPECT_EQ(vd.capacity(), 10);
//    vs.push_back("world");
//    EXPECT_EQ(vs.back(), "world");
//    EXPECT_EQ(vs.size(), 3);
//    EXPECT_EQ(vs.capacity(), 4);
//    vs.pop_back();
//    EXPECT_EQ(vs.back(), "hello");
//    EXPECT_EQ(vs.size(), 2);
//    EXPECT_EQ(vs.capacity(), 4);
//    vvi.push_back({4, 5, 6});
//    EXPECT_EQ(vvi.back(), vector<int>({4, 5, 6}));
//    EXPECT_EQ(vvi.size(), 3);
//    EXPECT_EQ(vvi.capacity(), 4);
//    vvi.pop_back();
//    EXPECT_EQ(vvi.back(), vector<int>({1, 2, 3}));
//    EXPECT_EQ(vvi.size(), 2);
//    EXPECT_EQ(vvi.capacity(), 4);
//}
//
//TEST_F(VectorTest, ERASE) {
//    vi.erase(vi.begin());
//    EXPECT_EQ(vi.front(), 2);
//    EXPECT_EQ(vi.size(), 4);
//    EXPECT_EQ(vi.capacity(), 5);
//    vi.erase(vi.end() - 1, vi.end());
//    EXPECT_EQ(vi.back(), 4);
//    EXPECT_EQ(vi.size(), 3);
//    EXPECT_EQ(vi.capacity(), 5);
//    vi.clear();
//    EXPECT_EQ(vi.size(), 0);
//    EXPECT_EQ(vi.capacity(), 5);
//    vf.erase(vf.begin());
//    EXPECT_EQ(vf.front(), 2.0f);
//    EXPECT_EQ(vf.size(), 4);
//    EXPECT_EQ(vf.capacity(), 5);
//    vf.erase(vf.end() - 1, vf.end());
//    EXPECT_EQ(vf.back(), 4.0f);
//    EXPECT_EQ(vf.size(), 3);
//    EXPECT_EQ(vf.capacity(), 5);
//    vf.clear();
//    EXPECT_EQ(vf.size(), 0);
//    EXPECT_EQ(vf.capacity(), 5);
//    vd.erase(vd.begin() + 1, vd.begin() + 2);
//    EXPECT_EQ(vd[1], 3.0f);
//    EXPECT_EQ(vd.size(), 4);
//    EXPECT_EQ(vd.capacity(), 5);
//    vs.erase(vs.begin() + 1, vs.begin() + 2);
//    EXPECT_EQ(vs.size(), 1);
//    EXPECT_EQ(vs.capacity(), 2);
//    vvi.erase(vvi.begin() + 1, vvi.begin() + 2);
//    EXPECT_EQ(vvi[1], vector<int>({1, 2, 3}));
//    EXPECT_EQ(vvi.size(), 1);
//    EXPECT_EQ(vvi.capacity(), 2);
//}
//
//TEST_F(VectorTest, INSERT) {
//    vi.insert(vi.begin());
//    EXPECT_EQ(vi.front(), 0);
//    EXPECT_EQ(vi.size(), 6);
//    EXPECT_EQ(vi.capacity(), 10);
//    vi.insert(vi.begin() + 1, 5);
//    EXPECT_EQ(vi[1], 5);
//    EXPECT_EQ(vi.size(), 7);
//    EXPECT_EQ(vi.capacity(), 10);
//    vector<int> temp_vi = {1, 2, 3};
//    vi.insert(vi.end(), temp_vi.begin(), temp_vi.end());
//    EXPECT_EQ(vi.back(), 3);
//    EXPECT_EQ(vi.size(), 10);
//    EXPECT_EQ(vi.capacity(), 10);
//    vf.insert(vf.begin());
//    EXPECT_EQ(vf.front(), 0.0f);
//    EXPECT_EQ(vf.size(), 6);
//    EXPECT_EQ(vf.capacity(), 10);
//    vf.insert(vf.begin() + 1, 5.0f);
//    EXPECT_EQ(vf[1], 5.0f);
//    EXPECT_EQ(vf.size(), 7);
//    EXPECT_EQ(vi.capacity(), 10);
//    vector<float> temp_vf = {1.0, 2.0, 3.0, 4.0};
//    vf.insert(vf.end(), temp_vf.begin(), temp_vf.end());
//    EXPECT_EQ(vf.back(), 4.0f);
//    EXPECT_EQ(vf.size(), 11);
//    EXPECT_EQ(vf.capacity(), 14);
//}
//
//TEST_F(VectorTest, ASSIGN) {
//    vi.assign(5, 2);
//    for (auto i : vi) EXPECT_EQ(i, 2);
//    vector<int> temp_vi = {1, 2};
//    vi.assign(temp_vi.begin(), temp_vi.end());
//    EXPECT_EQ(vi, temp_vi);
//    EXPECT_EQ(vi.size(), 2);
//    EXPECT_EQ(vi.capacity(), 5);
//    vi.assign({3, 3, 3, 3, 3, 3});
//    for (auto i : vi) EXPECT_EQ(i, 3);
//    EXPECT_EQ(vi.size(), 6);
//    EXPECT_EQ(vi.capacity(), 6);
//    vf.assign(5, 2.0f);
//    for (auto f : vf) EXPECT_EQ(f, 2.0f);
//    vector<float> temp_vf = {1.0f, 2.0f};
//    vf.assign(temp_vf.begin(), temp_vf.end());
//    EXPECT_EQ(vf, temp_vf);
//    EXPECT_EQ(vf.size(), 2);
//    EXPECT_EQ(vf.capacity(), 5);
//    vf.assign({3.1f, 3.1f, 3.1f, 3.1f, 3.1f, 3.1f});
//    for (auto f : vf) EXPECT_EQ(f, 3.1f);
//    EXPECT_EQ(vf.size(), 6);
//    EXPECT_EQ(vf.capacity(), 6);
//    vs.assign(5, "hi");
//    for (auto s : vs) EXPECT_EQ(s, "hi");
//    vector<string> temp_vs = {"world"};
//    vs.assign(temp_vs.begin(), temp_vs.end());
//    EXPECT_EQ(vs, temp_vs);
//    EXPECT_EQ(vs.size(), 1);
//    EXPECT_EQ(vs.capacity(), 5);
//    vs.assign({"cat", "cat", "cat"});
//    for (auto s : vs) EXPECT_EQ(s, "cat");
//    EXPECT_EQ(vs.size(), 3);
//    EXPECT_EQ(vs.capacity(), 5);
//}
//
//
////ListTest
//
//
//
//
//int main(int argc, char *argv[]) {
//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//    return 0;
//}


//
//  list_test.cpp
//  mini-stl
//
//  Created by cz-mac on 2021/12/21.
//
#include <gtest/gtest.h>
#include <string>
#include "stl_list.h"
#include "stl_deque.h"
using namespace ::MiniSTL;
using std::string;
//class ListTest : public testing::Test {
//protected:
//    virtual void SetUp() {
//        // set pre data
//        li = {1, 2, 3, 4, 5};
//        lf = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//        ld = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//        lb.resize(5);
//        ls = {"hello", "hello"};
//        lli = {{1, 2, 3}, {1, 2, 3}};
//    }
//    // pre structure
//    struct BAR {
//        int a;
//        double b;
//    };
//    list<int> li;
//    list<float> lf;
//    list<double> ld;
//    list<BAR> lb;
//    list<string> ls;
//    list<list<int>> lli;
//};
//
//TEST_F(ListTest, DEFAULT_CTOR) {
//    EXPECT_NO_THROW(list<int>());
//    EXPECT_NO_THROW(list<float>());
//    EXPECT_NO_THROW(list<double>());
//    EXPECT_NO_THROW(list<string>());
//    EXPECT_NO_THROW(list<BAR>());
//    EXPECT_NO_THROW(list<list<int>>());
//}
//
//TEST_F(ListTest, CTOR_WITH_SIZE) {
//    EXPECT_NO_THROW(list<int>(5));
//    EXPECT_NO_THROW(list<float>(5));
//    EXPECT_NO_THROW(list<double>(5));
//    EXPECT_NO_THROW(list<string>(5));
//    EXPECT_NO_THROW(list<BAR>(5));
//    EXPECT_NO_THROW(list<list<int>>(5));
//}
//
//TEST_F(ListTest, CTOR_WITH_VALUE) {
//    EXPECT_NO_THROW(list<int>(5, 5));
//    EXPECT_NO_THROW(list<float>(5, 5.0f));
//    EXPECT_NO_THROW(list<double>(5, 5.0f));
//    EXPECT_NO_THROW(list<string>(5, "hello"));
//    EXPECT_NO_THROW(list<BAR>(5, BAR()));
//    EXPECT_NO_THROW(list<list<int>>(5, {1, 2, 3}));
//}
//
//TEST_F(ListTest, CTOR_WITH_INPUTITERATOR) {
//    EXPECT_NO_THROW(list<int>(li.begin(), li.end()));
//    EXPECT_NO_THROW(list<int>(li.cbegin(), li.cend()));
//    EXPECT_NO_THROW(list<float>(lf.begin(), lf.end()));
//    EXPECT_NO_THROW(list<float>(lf.cbegin(), lf.cend()));
//    EXPECT_NO_THROW(list<double>(ld.begin(), ld.end()));
//    EXPECT_NO_THROW(list<double>(ld.cbegin(), ld.cend()));
//    EXPECT_NO_THROW(list<BAR>(lb.begin(), lb.end()));
//    EXPECT_NO_THROW(list<BAR>(lb.cbegin(), lb.cend()));
//    EXPECT_NO_THROW(list<list<int>>(lli.begin(), lli.end()));
//    EXPECT_NO_THROW(list<list<int>>(lli.cbegin(), lli.cend()));
//    // C API
//    int ai[5] = {1, 2, 3, 4, 5};
//    EXPECT_NO_THROW(list<int>(ai, ai + 5));
//    double ad[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//    EXPECT_NO_THROW(list<double>(ad, ad + 5));
//    string as[5] = {"a", "b", "c", "d", "f"};
//    EXPECT_NO_THROW(list<string>(as, as + 5));
//}
//
//TEST_F(ListTest, CTOR_WITH_INITIAL_LIST) {
//    EXPECT_NO_THROW(list<int>({1, 2, 3, 4, 5}));
//    EXPECT_NO_THROW(list<float>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}));
//    EXPECT_NO_THROW(list<double>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}));
//    EXPECT_NO_THROW(list<string>({"hello", "world"}));
//    EXPECT_NO_THROW(list<list<int>>({{1, 2, 3}, {4, 5, 6}}));
//}
//
//TEST_F(ListTest, COPY_CTOR) {
//    EXPECT_NO_THROW(list<int>(li));
//    EXPECT_NO_THROW(list<float>(lf));
//    EXPECT_NO_THROW(list<double>(ld));
//    EXPECT_NO_THROW(list<string>(ls));
//    EXPECT_NO_THROW(list<BAR>(lb));
//    EXPECT_NO_THROW(list<list<int>>(lli));
//}
//
//TEST_F(ListTest, MOVE_CTOR) {
//    EXPECT_NO_THROW(list<int>(std::move(li)));
//    EXPECT_NO_THROW(list<float>(std::move(lf)));
//    EXPECT_NO_THROW(list<double>(std::move(ld)));
//    EXPECT_NO_THROW(list<string>(std::move(ls)));
//    EXPECT_NO_THROW(list<BAR>(std::move(lb)));
//    EXPECT_NO_THROW(list<list<int>>(std::move(lli)));
//}
//
//// Node-based container cannot pass this test, as does std::list.
//
///* TEST_F(ListTest,DTOR){
//    list<int> *p = new list<int>(5,1);
//    int* p2i = &(p->begin().node->data);
//    EXPECT_EQ(*p2i,1);
//    delete p;
//    EXPECT_NE(*p2i,1);
//} */
//
//TEST_F(ListTest, COPYASSIGN_WITH_SELF) {
//    list<int> temp_li(5, 2);
//    li = temp_li;
//    for (auto i : li) EXPECT_EQ(i, 2);
//    list<float> temp_lf(5, 2.0f);
//    lf = temp_lf;
//    for (auto f : lf) EXPECT_EQ(f, 2.0f);
//    list<double> temp_ld(5, 2.235f);
//    ld = temp_ld;
//    for (auto d : ld) EXPECT_EQ(d, 2.235f);
//    list<string> temp_ls(5, "hello");
//    ls = temp_ls;
//    for (auto s : ls) EXPECT_EQ(s, "hello");
//    list<list<int>> temp_lli(5, {1, 2, 3});
//    lli = temp_lli;
//    for (auto li : lli) EXPECT_EQ(li, list<int>({1, 2, 3}));
//}
//
//TEST_F(ListTest, COPYASSIGN_WITH_INITIAL_LIST) {
//    li = {2, 2, 2, 2, 2};
//    for (auto i : li) EXPECT_EQ(i, 2);
//    lf = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
//    for (auto f : lf) EXPECT_EQ(f, 2.0f);
//    ld = {2.235f};
//    for (auto d : ld) EXPECT_EQ(d, 2.235f);
//    ls = {"hello", "hello", "hello"};
//    for (auto s : ls) EXPECT_EQ(s, "hello");
//    lli = {list<int>({1, 2, 3}), list<int>({1, 2, 3})};
//    for (auto li : lli) EXPECT_EQ(li, list<int>({1, 2, 3}));
//}
//
//TEST_F(ListTest, MOVEASSIGN_WITH_SELF) {
//    list<int> temp_li(5, 2);
//    li = std::move(temp_li);
//    for (auto i : li) EXPECT_EQ(i, 2);
//    for (auto i : temp_li) EXPECT_NE(i, 2);
//    list<float> temp_lf(5, 2.0f);
//    lf = std::move(temp_lf);
//    for (auto f : lf) EXPECT_EQ(f, 2.0f);
//    for (auto f : temp_lf) EXPECT_NE(f, 2.0f);
//    list<double> temp_ld(5, 2.235f);
//    ld = std::move(temp_ld);
//    for (auto d : ld) EXPECT_EQ(d, 2.235f);
//    for (auto d : temp_ld) EXPECT_NE(d, 2.235f);
//    list<string> temp_ls(5, "hello");
//    ls = std::move(temp_ls);
//    for (auto s : ls) EXPECT_EQ(s, "hello");
//    for (auto s : temp_ls) EXPECT_NE(s, "hello");
//    list<list<int>> temp_lli(5, {1, 2, 3});
//    lli = std::move(temp_lli);
//    for (auto li : lli) EXPECT_EQ(li, list<int>({1, 2, 3}));
//    for (auto li : temp_lli) EXPECT_NE(li, list<int>({1, 2, 3}));
//}
//
//TEST_F(ListTest, BEGIN_AND_END) {
//    for (auto it = li.begin(); it != li.end(); ++it) {
//        *it = 5;
//    }
//    for (auto it = li.cbegin(); it != li.cend(); ++it) EXPECT_EQ(*it, 5);
//    for (auto it = li.rbegin(); it != li.rend(); ++it) {
//        EXPECT_EQ(*it, 5);
//        *it = 3;
//    }
//    for (auto it = li.crbegin(); it != li.crend(); ++it) {
//        EXPECT_EQ(*it, 3);
//    }
//    for (auto it = lf.begin(); it != lf.end(); ++it) {
//        *it = 5.0f;
//    }
//    for (auto it = lf.cbegin(); it != lf.cend(); ++it) EXPECT_EQ(*it, 5.0f);
//    for (auto it = lf.rbegin(); it != lf.rend(); ++it) {
//        EXPECT_EQ(*it, 5.0f);
//        *it = 3.0f;
//    }
//    for (auto it = lf.crbegin(); it != lf.crend(); ++it) {
//        EXPECT_EQ(*it, 3.0f);
//    }
//    for (auto it = ld.begin(); it != ld.end(); ++it) {
//        *it = 5.0f;
//    }
//    for (auto it = ld.cbegin(); it != ld.cend(); ++it) EXPECT_EQ(*it, 5.0f);
//    for (auto it = ld.rbegin(); it != ld.rend(); ++it) {
//        EXPECT_EQ(*it, 5.0f);
//        *it = 3.0f;
//    }
//    for (auto it = ld.crbegin(); it != ld.crend(); ++it) {
//        EXPECT_EQ(*it, 3.0f);
//    }
//    for (auto it = ls.begin(); it != ls.end(); ++it) {
//        EXPECT_EQ(*it, "hello");
//        *it = "world";
//    }
//    for (auto it = ls.cbegin(); it != ls.cend(); ++it) EXPECT_EQ(*it, "world");
//    for (auto it = ls.rbegin(); it != ls.rend(); ++it) {
//        EXPECT_EQ(*it, "world");
//        *it = "hello";
//    }
//    for (auto it = ls.crbegin(); it != ls.crend(); ++it) {
//        EXPECT_EQ(*it, "hello");
//    }
//    for (auto it = lli.begin(); it != lli.end(); ++it) {
//        EXPECT_EQ(*it, list<int>({1, 2, 3}));
//        *it = {4, 5, 6};
//    }
//    for (auto it = lli.cbegin(); it != lli.cend(); ++it)
//        EXPECT_EQ(*it, list<int>({4, 5, 6}));
//    for (auto it = lli.rbegin(); it != lli.rend(); ++it) {
//        EXPECT_EQ(*it, list<int>({4, 5, 6}));
//        *it = {7, 8, 9};
//    }
//    for (auto it = lli.crbegin(); it != lli.crend(); ++it) {
//        EXPECT_EQ(*it, list<int>({7, 8, 9}));
//    }
//}
//
//TEST_F(ListTest, FRONT_AND_BACK) {
//    EXPECT_EQ(li.front(), 1);
//    li.front() = 2;
//    EXPECT_EQ(li.front(), 2);
//    EXPECT_EQ(li.back(), 5);
//    li.back() = 2;
//    EXPECT_EQ(li.back(), 2);
//    EXPECT_EQ(lf.front(), 1.0f);
//    lf.front() = 2.0f;
//    EXPECT_EQ(lf.front(), 2.0f);
//    EXPECT_EQ(lf.back(), 5.0f);
//    lf.back() = 2.0f;
//    EXPECT_EQ(lf.back(), 2.0f);
//    EXPECT_EQ(ld.front(), 1.0f);
//    ld.front() = 2.0f;
//    EXPECT_EQ(ld.front(), 2.0f);
//    EXPECT_EQ(ld.back(), 5.0f);
//    ld.back() = 2.0f;
//    EXPECT_EQ(ld.back(), 2.0f);
//    EXPECT_EQ(ls.front(), "hello");
//    ls.front() = "world";
//    EXPECT_EQ(ls.front(), "world");
//    EXPECT_EQ(ls.back(), "hello");
//    ls.back() = "world";
//    EXPECT_EQ(ls.back(), "world");
//    EXPECT_EQ(lli.front(), list<int>({1, 2, 3}));
//    lli.front() = {4, 5, 6};
//    EXPECT_EQ(lli.front(), list<int>({4, 5, 6}));
//    EXPECT_EQ(lli.back(), list<int>({1, 2, 3}));
//    lli.back() = {4, 5, 6};
//    EXPECT_EQ(lli.back(), list<int>({4, 5, 6}));
//}
//
//TEST_F(ListTest, SIZE) {
//    EXPECT_EQ(li.size(), 5);
//    li.resize(3);
//    EXPECT_EQ(li.size(), 3);
//    li.resize(10, 5);
//    EXPECT_EQ(li.size(), 10);
//    auto it = li.begin();
//    while (*it != 5) ++it;
//    while (it != li.end()) EXPECT_EQ(*it++, 5);
//}
//
//TEST_F(ListTest, COMPARATOR) {
//    list<int> temp_li = {1, 2, 3, 4, 5};
//    EXPECT_TRUE(temp_li == li);
//    EXPECT_FALSE(temp_li != li);
//    list<float> temp_lf(lf);
//    EXPECT_TRUE(temp_lf == lf);
//    EXPECT_FALSE(temp_lf != lf);
//    list<double> temp_ld(ld.cbegin(), ld.cend());
//    EXPECT_TRUE(temp_ld == ld);
//    EXPECT_FALSE(temp_ld != ld);
//    list<string> temp_ls(std::move(ls));
//    EXPECT_FALSE(temp_ls == ls);
//    EXPECT_TRUE(temp_ls != ls);
//    list<list<int>> temp_lli({{1, 2, 3}, {1, 2, 3}});
//    EXPECT_TRUE(temp_lli == lli);
//    EXPECT_FALSE(temp_lli != lli);
//}
//
//TEST_F(ListTest, PUSH_AND_POP) {
//    li.push_back(6);
//    EXPECT_EQ(li.back(), 6);
//    EXPECT_EQ(li.size(), 6);
//    li.pop_back();
//    EXPECT_EQ(li.back(), 5);
//    EXPECT_EQ(li.size(), 5);
//    li.push_front(0);
//    EXPECT_EQ(li.front(), 0);
//    EXPECT_EQ(li.size(), 6);
//    li.pop_fornt();
//    EXPECT_EQ(li.front(), 1);
//    EXPECT_EQ(li.size(), 5);
//    lf.push_back(6.0f);
//    EXPECT_EQ(lf.back(), 6.0f);
//    EXPECT_EQ(lf.size(), 6);
//    lf.pop_back();
//    EXPECT_EQ(lf.back(), 5.0f);
//    EXPECT_EQ(lf.size(), 5);
//    lf.push_front(0.0f);
//    EXPECT_EQ(lf.front(), 0.0f);
//    EXPECT_EQ(lf.size(), 6);
//    lf.pop_fornt();
//    EXPECT_EQ(lf.front(), 1.0f);
//    EXPECT_EQ(lf.size(), 5);
//    ld.push_back(6.0f);
//    EXPECT_EQ(ld.back(), 6.0f);
//    EXPECT_EQ(ld.size(), 6);
//    ld.pop_back();
//    EXPECT_EQ(ld.back(), 5.0f);
//    EXPECT_EQ(ld.size(), 5);
//    ld.push_front(0.0f);
//    EXPECT_EQ(ld.front(), 0);
//    EXPECT_EQ(ld.size(), 6);
//    ld.pop_fornt();
//    EXPECT_EQ(ld.front(), 1);
//    EXPECT_EQ(ld.size(), 5);
//    ls.push_back("world");
//    EXPECT_EQ(ls.back(), "world");
//    EXPECT_EQ(ls.size(), 3);
//    ls.pop_back();
//    EXPECT_EQ(ls.back(), "hello");
//    EXPECT_EQ(ls.size(), 2);
//    ls.push_front("miemie");
//    EXPECT_EQ(ls.front(), "miemie");
//    EXPECT_EQ(ls.size(), 3);
//    ls.pop_fornt();
//    EXPECT_EQ(ls.front(), "hello");
//    EXPECT_EQ(ls.size(), 2);
//    lli.push_back({4, 5, 6});
//    EXPECT_EQ(lli.back(), list<int>({4, 5, 6}));
//    EXPECT_EQ(lli.size(), 3);
//    lli.pop_back();
//    EXPECT_EQ(lli.back(), list<int>({1, 2, 3}));
//    EXPECT_EQ(lli.size(), 2);
//    lli.push_front({0, 0, 0});
//    EXPECT_EQ(lli.front(), list<int>({0, 0, 0}));
//    EXPECT_EQ(lli.size(), 3);
//    lli.pop_fornt();
//    EXPECT_EQ(lli.front(), list<int>({1, 2, 3}));
//    EXPECT_EQ(lli.size(), 2);
//}
//
//TEST_F(ListTest, ERASE) {
//    li.erase(li.begin());
//    EXPECT_EQ(li.front(), 2);
//    EXPECT_EQ(li.size(), 4);
//    li.clear();
//    EXPECT_EQ(li.size(), 0);
//    lf.erase(lf.begin());
//    EXPECT_EQ(lf.front(), 2.0f);
//    EXPECT_EQ(lf.size(), 4);
//    lf.clear();
//    EXPECT_EQ(lf.size(), 0);
//}
//
//TEST_F(ListTest, INSERT) {
//    li.insert(li.begin());
//    EXPECT_EQ(li.front(), 0);
//    EXPECT_EQ(li.size(), 6);
//    list<int> temp_li = {1, 2, 3};
//    li.insert(li.end(), temp_li.begin(), temp_li.end());
//    EXPECT_EQ(li.back(), 3);
//    EXPECT_EQ(li.size(), 9);
//    lf.insert(lf.begin());
//    EXPECT_EQ(lf.front(), 0.0f);
//    EXPECT_EQ(lf.size(), 6);
//    list<float> temp_lf = {1.0, 2.0, 3.0, 4.0};
//    lf.insert(lf.end(), temp_lf.begin(), temp_lf.end());
//    EXPECT_EQ(lf.back(), 4.0f);
//    EXPECT_EQ(lf.size(), 10);
//}
//
//TEST_F(ListTest, ASSIGN) {
//    li.assign(5, 2);
//    for (auto i : li) EXPECT_EQ(i, 2);
//    list<int> temp_li = {1, 2};
//    li.assign(temp_li.begin(), temp_li.end());
//    EXPECT_EQ(li, temp_li);
//    EXPECT_EQ(li.size(), 2);
//    li.assign({3, 3, 3, 3, 3, 3});
//    for (auto i : li) EXPECT_EQ(i, 3);
//    EXPECT_EQ(li.size(), 6);
//    lf.assign(5, 2.0f);
//    for (auto f : lf) EXPECT_EQ(f, 2.0f);
//    list<float> temp_lf = {1.0f, 2.0f};
//    lf.assign(temp_lf.begin(), temp_lf.end());
//    EXPECT_EQ(lf, temp_lf);
//    EXPECT_EQ(lf.size(), 2);
//    lf.assign({3.1f, 3.1f, 3.1f, 3.1f, 3.1f, 3.1f});
//    for (auto f : lf) EXPECT_EQ(f, 3.1f);
//    EXPECT_EQ(lf.size(), 6);
//    ls.assign(5, "hi");
//    for (auto s : ls) EXPECT_EQ(s, "hi");
//    list<string> temp_ls = {"world"};
//    ls.assign(temp_ls.begin(), temp_ls.end());
//    EXPECT_EQ(ls, temp_ls);
//    EXPECT_EQ(ls.size(), 1);
//    ls.assign({"cat", "cat", "cat"});
//    for (auto s : ls) EXPECT_EQ(s, "cat");
//    EXPECT_EQ(ls.size(), 3);
//}
//
//TEST_F(ListTest, UNIQUE) {
//    ls.unique();
//    EXPECT_EQ(ls.size(), 1);
//    EXPECT_EQ(ls.front(), "hello");
//    lli.unique();
//    EXPECT_EQ(lli.size(), 1);
//    EXPECT_EQ(lli.front(), list<int>({1, 2, 3}));
//}
//
//TEST_F(ListTest, SPLICE) {
//    list<int> temp_li = {6, 7, 8, 9, 10};
//    li.splice(li.end(), temp_li);
//    int i = 1;
//    for (auto it = li.cbegin(); it != li.cend(); ++it, ++i) EXPECT_EQ(*it, i);
//    EXPECT_EQ(temp_li.size(), 0);
//    list<float> temp_lf = {6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
//    lf.splice(lf.begin(), temp_lf, temp_lf.begin());
//    EXPECT_EQ(lf.size(), 6);
//    EXPECT_EQ(lf.front(), 6.0f);
//    lf.splice(lf.end(), temp_lf, temp_lf.begin());
//    EXPECT_EQ(lf.size(), 7);
//    EXPECT_EQ(lf.back(), 7.0f);
//    EXPECT_EQ(temp_lf.size(), 3);
//    EXPECT_EQ(temp_lf.front(), 8.0f);
//    list<string> temp_ls = {"world", "world"};
//    ls.splice(ls.end(), temp_ls, temp_ls.begin(), temp_ls.end());
//    EXPECT_EQ(ls.size(), 4);
//    EXPECT_EQ(ls.back(), "world");
//    EXPECT_EQ(temp_ls.size(), 0);
//}
//
//TEST_F(ListTest, MERGE) {
//    list<int> temp_li1 = {1, 3, 5, 7, 9};
//    list<int> temp_li2 = {2, 4, 6, 8, 10};
//    temp_li1.merge(temp_li2);
//    int i = 1;
//    for (auto it = temp_li1.cbegin(); it != temp_li1.cend(); ++it, ++i)
//        EXPECT_EQ(*it, i);
//}
//
//TEST_F(ListTest, REVERSE) {
//    list<int> temp_li(li);
//    li.reverse();
//    auto it = li.begin();
//    auto rit = temp_li.rbegin();
//    while (it != li.end()) EXPECT_EQ(*it++, *rit++);
//}
//
//TEST_F(ListTest, SORT) {
//    li = {5, 3, 1, 2, 6, 7, 10, 9, 8, 4};
//    li.sort();
//    int i = 1;
//    for (auto it = li.cbegin(); it != li.cend(); ++it, ++i) EXPECT_EQ(*it, i);
//}
//
//TEST_F(ListTest, REMOVE) {
//    li.remove(1);
//    EXPECT_EQ(li.size(), 4);
//    EXPECT_EQ(li.front(), 2);
//    li.remove(5);
//    EXPECT_EQ(li.size(), 3);
//    EXPECT_EQ(li.back(), 4);
//    ls.remove("hello");
//    EXPECT_EQ(ls.size(), 0);
//}
class DequeTest : public testing::Test {
protected:
    virtual void SetUp() {
        // set pre data
        di = {1, 2, 3, 4, 5};
        df = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        dd = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        db.resize(5);
        ds = {"hello", "hello"};
        ddi = {{1, 2, 3}, {1, 2, 3}};
    }
    // pre structure
    struct BAR {
        int a;
        double b;
    };
    deque<int> di;
    deque<float> df;
    deque<double> dd;
    deque<BAR> db;
    deque<string> ds;
    deque<deque<int>> ddi;
};

TEST_F(DequeTest, DEFAULT_CTOR) {
    EXPECT_NO_THROW(deque<int>());
    EXPECT_NO_THROW(deque<float>());
    EXPECT_NO_THROW(deque<double>());
    EXPECT_NO_THROW(deque<string>());
    EXPECT_NO_THROW(deque<BAR>());
    EXPECT_NO_THROW(deque<deque<int>>());
}

TEST_F(DequeTest, CTOR_WITH_SIZE) {
    EXPECT_NO_THROW(deque<int>(5));
    EXPECT_NO_THROW(deque<float>(5));
    EXPECT_NO_THROW(deque<double>(5));
    EXPECT_NO_THROW(deque<string>(5));
    EXPECT_NO_THROW(deque<BAR>(5));
    EXPECT_NO_THROW(deque<deque<int>>(5));
}

TEST_F(DequeTest, CTOR_WITH_VALUE) {
    EXPECT_NO_THROW(deque<int>(5, 5));
    EXPECT_NO_THROW(deque<float>(5, 5.0f));
    EXPECT_NO_THROW(deque<double>(5, 5.0f));
    EXPECT_NO_THROW(deque<string>(5, "hello"));
    EXPECT_NO_THROW(deque<BAR>(5, BAR()));
    EXPECT_NO_THROW(deque<deque<int>>(5, {1, 2, 3}));
}

TEST_F(DequeTest, CTOR_WITH_INPUTITERATOR) {
    EXPECT_NO_THROW(deque<int>(di.begin(), di.end()));
    EXPECT_NO_THROW(deque<int>(di.cbegin(), di.cend()));
    EXPECT_NO_THROW(deque<float>(df.begin(), df.end()));
    EXPECT_NO_THROW(deque<float>(df.cbegin(), df.cend()));
    EXPECT_NO_THROW(deque<double>(dd.begin(), dd.end()));
    EXPECT_NO_THROW(deque<double>(dd.cbegin(), dd.cend()));
    EXPECT_NO_THROW(deque<BAR>(db.begin(), db.end()));
    EXPECT_NO_THROW(deque<BAR>(db.cbegin(), db.cend()));
    EXPECT_NO_THROW(deque<deque<int>>(ddi.begin(), ddi.end()));
    EXPECT_NO_THROW(deque<deque<int>>(ddi.cbegin(), ddi.cend()));
    // C API
    int ai[5] = {1, 2, 3, 4, 5};
    EXPECT_NO_THROW(deque<int>(ai, ai + 5));
    double ad[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    EXPECT_NO_THROW(deque<double>(ad, ad + 5));
    string as[5] = {"a", "b", "c", "d", "f"};
    EXPECT_NO_THROW(deque<string>(as, as + 5));
}

TEST_F(DequeTest, CTOR_WITH_INITIAL_LIST) {
    EXPECT_NO_THROW(deque<int>({1, 2, 3, 4, 5}));
    EXPECT_NO_THROW(deque<float>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}));
    EXPECT_NO_THROW(deque<double>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}));
    EXPECT_NO_THROW(deque<string>({"hello", "world"}));
    EXPECT_NO_THROW(deque<deque<int>>({{1, 2, 3}, {4, 5, 6}}));
}

TEST_F(DequeTest, COPY_CTOR) {
    EXPECT_NO_THROW(deque<int>(di));
    EXPECT_NO_THROW(deque<float>(df));
    EXPECT_NO_THROW(deque<double>(dd));
    EXPECT_NO_THROW(deque<string>(ds));
    EXPECT_NO_THROW(deque<BAR>(db));
    EXPECT_NO_THROW(deque<deque<int>>(ddi));
}

TEST_F(DequeTest, MOVE_CTOR) {
    EXPECT_NO_THROW(deque<int>(std::move(di)));
    EXPECT_NO_THROW(deque<float>(std::move(df)));
    EXPECT_NO_THROW(deque<double>(std::move(dd)));
    EXPECT_NO_THROW(deque<string>(std::move(ds)));
    EXPECT_NO_THROW(deque<BAR>(std::move(db)));
    EXPECT_NO_THROW(deque<deque<int>>(std::move(ddi)));
}

TEST_F(DequeTest, DTOR) {
    deque<int> *p = new deque<int>(5, 1);
    int *p2i = &((*p)[0]);
    EXPECT_EQ(*p2i, 1);
    delete p;
    EXPECT_NE(*p2i, 1);
}

TEST_F(DequeTest, COPYASSIGN_WITH_SELF) {
    deque<int> temp_di(5, 2);
    di = temp_di;
    for (auto i : di) EXPECT_EQ(i, 2);
    deque<float> temp_df(5, 2.0f);
    df = temp_df;
    for (auto f : df) EXPECT_EQ(f, 2.0f);
    deque<double> temp_dd(5, 2.235f);
    dd = temp_dd;
    for (auto d : dd) EXPECT_EQ(d, 2.235f);
    deque<string> temp_ds(5, "hello");
    ds = temp_ds;
    for (auto s : ds) EXPECT_EQ(s, "hello");
    deque<deque<int>> temp_ddi(5, {1, 2, 3});
    ddi = temp_ddi;
    for (auto di : ddi) EXPECT_EQ(di, deque<int>({1, 2, 3}));
}

TEST_F(DequeTest, COPYASSIGN_WITH_INITIAL_LIST) {
    di = {2, 2, 2, 2, 2};
    for (auto i : di) EXPECT_EQ(i, 2);
    df = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
    for (auto f : df) EXPECT_EQ(f, 2.0f);
    dd = {2.235f};
    for (auto d : dd) EXPECT_EQ(d, 2.235f);
    ds = {"hello", "hello", "hello"};
    for (auto s : ds) EXPECT_EQ(s, "hello");
    ddi = {deque<int>({1, 2, 3}), deque<int>({1, 2, 3})};
    for (auto di : ddi) EXPECT_EQ(di, deque<int>({1, 2, 3}));
}

TEST_F(DequeTest, MOVEASSIGN_WITH_SELF) {
    deque<int> temp_di(5, 2);
    di = std::move(temp_di);
    for (auto i : di) EXPECT_EQ(i, 2);
    for (auto i : temp_di) EXPECT_NE(i, 2);
    deque<float> temp_df(5, 2.0f);
    df = std::move(temp_df);
    for (auto f : df) EXPECT_EQ(f, 2.0f);
    for (auto f : temp_df) EXPECT_NE(f, 2.0f);
    deque<double> temp_dd(5, 2.235f);
    dd = std::move(temp_dd);
    for (auto d : dd) EXPECT_EQ(d, 2.235f);
    for (auto d : temp_dd) EXPECT_NE(d, 2.235f);
    deque<string> temp_ds(5, "hello");
    ds = std::move(temp_ds);
    for (auto s : ds) EXPECT_EQ(s, "hello");
    for (auto s : temp_ds) EXPECT_NE(s, "hello");
    deque<deque<int>> temp_ddi(5, {1, 2, 3});
    ddi = std::move(temp_ddi);
    for (auto di : ddi) EXPECT_EQ(di, deque<int>({1, 2, 3}));
    for (auto di : temp_ddi) EXPECT_NE(di, deque<int>({1, 2, 3}));
}

TEST_F(DequeTest, BEGIN_AND_END) {
    for (auto it = di.begin(); it != di.end(); ++it) {
        EXPECT_EQ(*it, it - di.begin() + 1);
        *it = 5;
    }
    for (auto it = di.cbegin(); it != di.cend(); ++it) EXPECT_EQ(*it, 5);
    for (auto it = di.rbegin(); it != di.rend(); ++it) {
        EXPECT_EQ(*it, 5);
        *it = 3;
    }
    for (auto it = di.crbegin(); it != di.crend(); ++it) {
        EXPECT_EQ(*it, 3);
    }
    for (auto it = df.begin(); it != df.end(); ++it) {
        EXPECT_EQ(*it, it - df.begin() + 1.0f);
        *it = 5.0f;
    }
    for (auto it = df.cbegin(); it != df.cend(); ++it) EXPECT_EQ(*it, 5.0f);
    for (auto it = df.rbegin(); it != df.rend(); ++it) {
        EXPECT_EQ(*it, 5.0f);
        *it = 3.0f;
    }
    for (auto it = df.crbegin(); it != df.crend(); ++it) {
        EXPECT_EQ(*it, 3.0f);
    }
    for (auto it = dd.begin(); it != dd.end(); ++it) {
        EXPECT_EQ(*it, it - dd.begin() + 1.0f);
        *it = 5.0f;
    }
    for (auto it = dd.cbegin(); it != dd.cend(); ++it) EXPECT_EQ(*it, 5.0f);
    for (auto it = dd.rbegin(); it != dd.rend(); ++it) {
        EXPECT_EQ(*it, 5.0f);
        *it = 3.0f;
    }
    for (auto it = dd.crbegin(); it != dd.crend(); ++it) {
        EXPECT_EQ(*it, 3.0f);
    }
    for (auto it = ds.begin(); it != ds.end(); ++it) {
        EXPECT_EQ(*it, "hello");
        *it = "world";
    }
    for (auto it = ds.cbegin(); it != ds.cend(); ++it) EXPECT_EQ(*it, "world");
    for (auto it = ds.rbegin(); it != ds.rend(); ++it) {
        EXPECT_EQ(*it, "world");
        *it = "hello";
    }
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        EXPECT_EQ(*it, "hello");
    }
    for (auto it = ddi.begin(); it != ddi.end(); ++it) {
        EXPECT_EQ(*it, deque<int>({1, 2, 3}));
        *it = {4, 5, 6};
    }
    for (auto it = ddi.cbegin(); it != ddi.cend(); ++it)
        EXPECT_EQ(*it, deque<int>({4, 5, 6}));
    for (auto it = ddi.rbegin(); it != ddi.rend(); ++it) {
        EXPECT_EQ(*it, deque<int>({4, 5, 6}));
        *it = {7, 8, 9};
    }
    for (auto it = ddi.crbegin(); it != ddi.crend(); ++it) {
        EXPECT_EQ(*it, deque<int>({7, 8, 9}));
    }
}

TEST_F(DequeTest, FRONT_AND_BACK) {
    EXPECT_EQ(di.front(), 1);
    di.front() = 2;
    EXPECT_EQ(di.front(), 2);
    EXPECT_EQ(di.back(), 5);
    di.back() = 2;
    EXPECT_EQ(di.back(), 2);
    EXPECT_EQ(df.front(), 1.0f);
    df.front() = 2.0f;
    EXPECT_EQ(df.front(), 2.0f);
    EXPECT_EQ(df.back(), 5.0f);
    df.back() = 2.0f;
    EXPECT_EQ(df.back(), 2.0f);
    EXPECT_EQ(dd.front(), 1.0f);
    dd.front() = 2.0f;
    EXPECT_EQ(dd.front(), 2.0f);
    EXPECT_EQ(dd.back(), 5.0f);
    dd.back() = 2.0f;
    EXPECT_EQ(dd.back(), 2.0f);
    EXPECT_EQ(ds.front(), "hello");
    ds.front() = "world";
    EXPECT_EQ(ds.front(), "world");
    EXPECT_EQ(ds.back(), "hello");
    ds.back() = "world";
    EXPECT_EQ(ds.back(), "world");
    EXPECT_EQ(ddi.front(), deque<int>({1, 2, 3}));
    ddi.front() = {4, 5, 6};
    EXPECT_EQ(ddi.front(), deque<int>({4, 5, 6}));
    EXPECT_EQ(ddi.back(), deque<int>({1, 2, 3}));
    ddi.back() = {4, 5, 6};
    EXPECT_EQ(ddi.back(), deque<int>({4, 5, 6}));
}

TEST_F(DequeTest, RANDOMACCESS) {
    for (size_t i = 0; i != di.size(); ++i) EXPECT_EQ(di[i], i + 1);
    for (size_t i = 0; i != df.size(); ++i) EXPECT_EQ(df[i], i + 1.0f);
    for (size_t i = 0; i != dd.size(); ++i) EXPECT_EQ(dd[i], i + 1.0f);
    for (size_t i = 0; i != ds.size(); ++i) EXPECT_EQ(ds[i], "hello");
    for (size_t i = 0; i != ddi.size(); ++i)
        EXPECT_EQ(ddi[i], deque<int>({1, 2, 3}));
}

TEST_F(DequeTest, SIZE_AND_CAPACITY) {
    EXPECT_EQ(di.size(), 5);
    di.resize(3);
    EXPECT_EQ(di.size(), 3);
    di.resize(10, 5);
    for (size_t i = 3; i != 10; ++i) EXPECT_EQ(di[i], 5);
    EXPECT_EQ(di.size(), 10);
}

TEST_F(DequeTest, COMPARATOR) {
    deque<int> temp_di = {1, 2, 3, 4, 5};
    EXPECT_TRUE(temp_di == di);
    EXPECT_FALSE(temp_di != di);
    deque<float> temp_df(df);
    EXPECT_TRUE(temp_df == df);
    EXPECT_FALSE(temp_df != df);
    deque<double> temp_dd(dd.cbegin(), dd.cend());
    EXPECT_TRUE(temp_dd == dd);
    EXPECT_FALSE(temp_dd != dd);
    deque<string> temp_ds(std::move(ds));
    EXPECT_FALSE(temp_ds == ds);
    EXPECT_TRUE(temp_ds != ds);
    deque<deque<int>> temp_ddi({{1, 2, 3}, {1, 2, 3}});
    EXPECT_TRUE(temp_ddi == ddi);
    EXPECT_FALSE(temp_ddi != ddi);
}

TEST_F(DequeTest, PUSH_AND_POP) {
    di.push_back(6);
    EXPECT_EQ(di.back(), 6);
    EXPECT_EQ(di.size(), 6);
    di.pop_back();
    EXPECT_EQ(di.back(), 5);
    EXPECT_EQ(di.size(), 5);
    df.push_back(6.0f);
    EXPECT_EQ(df.back(), 6.0f);
    EXPECT_EQ(df.size(), 6);
    df.pop_back();
    EXPECT_EQ(df.back(), 5.0f);
    EXPECT_EQ(df.size(), 5);
    dd.push_back(6.0f);
    EXPECT_EQ(dd.back(), 6.0f);
    EXPECT_EQ(dd.size(), 6);
    dd.pop_back();
    EXPECT_EQ(dd.back(), 5.0f);
    EXPECT_EQ(dd.size(), 5);
    ds.push_back("world");
    EXPECT_EQ(ds.back(), "world");
    EXPECT_EQ(ds.size(), 3);
    ds.pop_back();
    EXPECT_EQ(ds.back(), "hello");
    EXPECT_EQ(ds.size(), 2);
    ddi.push_back({4, 5, 6});
    EXPECT_EQ(ddi.back(), deque<int>({4, 5, 6}));
    EXPECT_EQ(ddi.size(), 3);
    ddi.pop_back();
    EXPECT_EQ(ddi.back(), deque<int>({1, 2, 3}));
    EXPECT_EQ(ddi.size(), 2);
}

TEST_F(DequeTest, ERASE) {
    di.erase(di.begin());
    EXPECT_EQ(di.front(), 2);
    EXPECT_EQ(di.size(), 4);
    di.erase(di.end() - 1, di.end());
    EXPECT_EQ(di.back(), 4);
    EXPECT_EQ(di.size(), 3);
    di.clear();
    EXPECT_EQ(di.size(), 0);
    df.erase(df.begin());
    EXPECT_EQ(df.front(), 2.0f);
    EXPECT_EQ(df.size(), 4);
    df.erase(df.end() - 1, df.end());
    EXPECT_EQ(df.back(), 4.0f);
    EXPECT_EQ(df.size(), 3);
    df.clear();
    EXPECT_EQ(df.size(), 0);
    dd.erase(dd.begin() + 1, dd.begin() + 2);
    EXPECT_EQ(dd[1], 3.0f);
    EXPECT_EQ(dd.size(), 4);
    ds.erase(ds.begin() + 1, ds.begin() + 2);
    EXPECT_EQ(ds.size(), 1);
    ddi.erase(ddi.begin() + 1, ddi.begin() + 2);
    EXPECT_EQ(ddi[1], deque<int>({1, 2, 3}));
    EXPECT_EQ(ddi.size(), 1);
}

TEST_F(DequeTest, INSERT) {
    di.insert(di.begin());
    EXPECT_EQ(di.front(), 0);
    EXPECT_EQ(di.size(), 6);
    di.insert(di.begin() + 1, 5);
    EXPECT_EQ(di[1], 5);
    EXPECT_EQ(di.size(), 7);
    deque<int> temp_di = {1, 2, 3};
    di.insert(di.end(), temp_di.begin(), temp_di.end());
    EXPECT_EQ(di.back(), 3);
    EXPECT_EQ(di.size(), 10);
    df.insert(df.begin());
    EXPECT_EQ(df.front(), 0.0f);
    EXPECT_EQ(df.size(), 6);
    df.insert(df.begin() + 1, 5.0f);
    EXPECT_EQ(df[1], 5.0f);
    EXPECT_EQ(df.size(), 7);
    deque<float> temp_df = {1.0, 2.0, 3.0, 4.0};
    df.insert(df.end(), temp_df.begin(), temp_df.end());
    EXPECT_EQ(df.back(), 4.0f);
    EXPECT_EQ(df.size(), 11);
}

TEST_F(DequeTest, ASSIGN) {
    di.assign(5, 2);
    for (auto i : di) EXPECT_EQ(i, 2);
    deque<int> temp_di = {1, 2};
    di.assign(temp_di.begin(), temp_di.end());
    EXPECT_EQ(di, temp_di);
    EXPECT_EQ(di.size(), 2);
    di.assign({3, 3, 3, 3, 3, 3});
    for (auto i : di) EXPECT_EQ(i, 3);
    EXPECT_EQ(di.size(), 6);
    df.assign(5, 2.0f);
    for (auto f : df) EXPECT_EQ(f, 2.0f);
    deque<float> temp_df = {1.0f, 2.0f};
    df.assign(temp_df.begin(), temp_df.end());
    EXPECT_EQ(df, temp_df);
    EXPECT_EQ(df.size(), 2);
    df.assign({3.1f, 3.1f, 3.1f, 3.1f, 3.1f, 3.1f});
    for (auto f : df) EXPECT_EQ(f, 3.1f);
    EXPECT_EQ(df.size(), 6);
    ds.assign(5, "hi");
    for (auto s : ds) EXPECT_EQ(s, "hi");
    deque<string> temp_ds = {"world"};
    ds.assign(temp_ds.begin(), temp_ds.end());
    EXPECT_EQ(ds, temp_ds);
    EXPECT_EQ(ds.size(), 1);
    ds.assign({"cat", "cat", "cat"});
    for (auto s : ds) EXPECT_EQ(s, "cat");
    EXPECT_EQ(ds.size(), 3);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
