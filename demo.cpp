#define __TUPLE_NAMESPACE foo

#include "include/tuple.hpp"
#include <iostream>
#include <cassert>

int main()
{
  using namespace foo;

  using type0 = tuple<>;
  assert(std::tuple_size<type0>::value == 0);
  assert((std::is_empty<std::tuple_element<0,type0>>::value == true));

  assert(type0{} == type0{});
  assert(!(type0{} != type0{}));
  assert(!(type0{} < type0{}));
  assert(!(type0{} > type0{}));

  using type1 = tuple<int>;
  assert(std::tuple_size<type1>::value == 1);
  assert((
    std::is_same<
      typename std::tuple_element<0,type1>::type,
      int
    >::value
  ));

  type1 t1;
  assert(std::get<0>(t1) == 0);

  type1 t2(13);
  assert(std::get<0>(t2) == 13);

  assert(t1 <= t2);
  assert(t1 <  t2);

  assert(t2 >= t2);
  assert(t2 >  t1);

  assert(t1 == t1);
  assert(t1 <= t1);
  assert(t1 >= t1);

  using type2 = tuple<int, float>;
  assert(std::tuple_size<type2>::value == 2);
  assert((
    std::is_same<
      typename std::tuple_element<0,type2>::type,
      int
    >::value
  ));
  assert((
    std::is_same<
      typename std::tuple_element<1,type2>::type,
      float
    >::value
  ));

  type2 t3;
  assert(std::get<0>(t3) == 0);
  assert(std::get<1>(t3) == 0);

  type2 t4(13,7);
  assert(std::get<0>(t4) == 13);
  assert(std::get<1>(t4) == 7);


  assert((
    std::is_same<
      decltype(std::get<0>(t3)),
      int&
    >::value
  ));


  assert((
    std::is_same<
      decltype(std::get<1>(t3)),
      float&
    >::value
  ));


  assert((
    std::is_same<
      decltype(std::get<0>(static_cast<const type2&>(t3))),
      const int&
    >::value
  ));


  assert((
    std::is_same<
      decltype(std::get<1>(static_cast<const type2&>(t3))),
      const float&
    >::value
  ));


  assert((
    std::is_same<
      decltype(std::get<0>(std::move(t3))),
      int&&
    >::value
  ));


  assert((
    std::is_same<
      decltype(std::get<1>(std::move(t3))),
      float&&
    >::value
  ));
      
  using type3 = tuple<int,int,int>;
  type3 t5(1,2,3);
  assert(std::get<0>(t5) == 1);
  assert(std::get<1>(t5) == 2);
  assert(std::get<2>(t5) == 3);

  type3 t6{};
  assert(std::get<0>(t6) == 0);
  assert(std::get<1>(t6) == 0);
  assert(std::get<2>(t6) == 0);

  assert(t5 != t6);
  assert(t5 >  t6);
  assert(t6 <  t5);
  assert(t5 >= t6);
  assert(t6 <= t5);

  t6 = t5;
  assert(std::get<0>(t6) == 1);
  assert(std::get<1>(t6) == 2);
  assert(std::get<2>(t6) == 3);

  assert(t5 == t6);
  assert(t5 <= t6);
  assert(t5 >= t6);

  using type4 = tuple<type3,type3>;
  type4 t7(type3(1,2,3), type3(4,5,6));
  assert(std::get<0>(std::get<0>(t7)) == 1);
  assert(std::get<1>(std::get<0>(t7)) == 2);
  assert(std::get<2>(std::get<0>(t7)) == 3);

  assert(std::get<0>(std::get<1>(t7)) == 4);
  assert(std::get<1>(std::get<1>(t7)) == 5);
  assert(std::get<2>(std::get<1>(t7)) == 6);

  type3 t8(1,2,3);
  assert(std::get<0>(t5) == 1);
  assert(std::get<1>(t5) == 2);
  assert(std::get<2>(t5) == 3);

  int a, b, c;
  tie(a,b,c) = t5;
  assert(a == 1);
  assert(b == 2);
  assert(c == 3);

  assert(tie(a,b,c) == t5);
  assert(tie(a,b,c) <= t5);
  assert(tie(a,b,c) >= t5);

  auto t9 = make_tuple(std::string("hi"));
  tuple<std::string> t10;
  t10 = std::move(t9);
  assert(std::get<0>(t9) == "");
  assert(std::get<0>(t10) == "hi");

  assert(make_tuple(1,2,3) < make_tuple(1,2,4));
  assert(make_tuple(1,2,4) > make_tuple(1,2,3));

  auto x = tie(b);
  x = x;  // ensure that tuple<tuple<int,int,int>&>::operator=(tuple<tuple<int,int,int>&>) has not been deleted

  {
    int x;
    tie(x, ignore) = make_tuple(13, std::string("hello"));
    assert(x == 13);

    auto one_ignore = make_tuple(ignore);
    assert((std::is_empty<decltype(one_ignore)>::value));

    auto two_ignore = make_tuple(ignore, ignore);
    assert((std::is_empty<decltype(two_ignore)>::value));
  }

  {
    auto nested_empty = make_tuple(ignore, make_tuple(ignore));
    std::get<0>(nested_empty);

    assert((std::is_empty<decltype(nested_empty)>::value));
  }

  {
    auto t = make_tuple(1, 13., std::string("hello"));
    assert(std::get<int>(t) == 1);
    assert(std::get<double>(t) == 13.);
    assert(std::get<std::string>(t) == "hello");
  }

  std::cout << "OK" << std::endl;

  return 0;
}

