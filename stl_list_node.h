//
//  stl_list_node.h
//  mini-stl
//
//  Created by cz-mac on 2021/12/21.
//

#pragma once

namespace MiniSTL {

template <class T>
struct __list_node {
    __list_node *prev;
    __list_node *next;
    T data;
};

}  // namespace MiniSTL
