//
//  stl_list_node.h
//  mini-stl
//
//  Created by cz-mac on 2021/12/21.
//

#pragma once

namespace MiniSTL {
//双向链表的结构
template <class T>
struct __list_node {
    __list_node *prev; //前驱
    __list_node *next; //后继
    T data; //数据域
};

}  // namespace MiniSTL
