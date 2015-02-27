#define __TUPLE_NAMESPACE foo

#include <tuple>
#include <iostream>
#include <cassert>

int main()
{
  using type0 = foo::tuple<>;
  assert(std::tuple_size<type0>::value == 0);
  assert((std::is_empty<std::tuple_element<0,type0>>::value == true));

  assert(type0{} == type0{});
  assert(!(type0{} != type0{}));
  assert(!(type0{} < type0{}));
  assert(!(type0{} > type0{}));

  using type1 = foo::tuple<int>;
  assert(std::tuple_size<type1>::value == 1);
  assert((
    std::is_same<
      std::tuple_element_t<0,type1>,
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

  using type2 = foo::tuple<int, float>;
  assert(std::tuple_size<type2>::value == 2);
  assert((
    std::is_same<
      std::tuple_element_t<0,type2>,
      int
    >::value
  ));
  assert((
    std::is_same<
      std::tuple_element_t<1,type2>,
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
      
  using type3 = foo::tuple<int,int,int>;
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

  using type4 = foo::tuple<type3,type3>;
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
  foo::tie(a,b,c) = t5;
  assert(a == 1);
  assert(b == 2);
  assert(c == 3);

  assert(foo::tie(a,b,c) == t5);
  assert(foo::tie(a,b,c) <= t5);
  assert(foo::tie(a,b,c) >= t5);

  auto t9 = foo::make_tuple(std::string("hi"));
  foo::tuple<std::string> t10;
  t10 = std::move(t9);
  assert(std::get<0>(t9) == "");
  assert(std::get<0>(t10) == "hi");

  assert(foo::make_tuple(1,2,3) < foo::make_tuple(1,2,4));
  assert(foo::make_tuple(1,2,4) > foo::make_tuple(1,2,3));

  auto x = foo::tie(b);
  x = x;  // ensure that tuple<tuple<int,int,int>&>::operator=(tuple<tuple<int,int,int>&>) has not been deleted

  {
    int x;
    foo::tie(x, foo::ignore) = foo::make_tuple(13, std::string("hello"));

    assert(x == 13);

    //auto one_ignore = foo::make_tuple(foo::ignore);
    //assert((std::is_empty<decltype(one_ignore)>::value));
    using type1 = foo::__tuple_leaf_base<decltype(foo::ignore)>;
    std::cout << "is_empty<__tuple_leaf_base>: " << std::is_empty<type1>::value << std::endl;

    using type2 = foo::__tuple_leaf<0,decltype(foo::ignore)>;
    std::cout << "is_empty<__tuple_leaf>: " << std::is_empty<type2>::value << std::endl;

    using type3 = foo::__tuple_base<
      foo::__tuple_index_sequence<0>,
      decltype(foo::ignore)
    >;
    std::cout << "is_empty<__tuple_base>: " << std::is_empty<type3>::value << std::endl;

    using type4 = foo::tuple<decltype(foo::ignore)>;
    std::cout << "is_empty<tuple>: " << std::is_empty<type4>::value << std::endl;
  }

  return 0;
}

