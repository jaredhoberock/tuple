#define __TUPLE_NAMESPACE foo

#include <tuple>
#include <iostream>
#include <cassert>

int main()
{
  using type0 = foo::tuple<>;
  assert(std::tuple_size<type0>::value == 0);
  assert((std::is_empty<std::tuple_element<0,type0>>::value == true));

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

  t6 = t5;
  assert(std::get<0>(t6) == 1);
  assert(std::get<1>(t6) == 2);
  assert(std::get<2>(t6) == 3);

  using type4 = foo::tuple<type3,type3>;
  type4 t7(type3(1,2,3), type3(4,5,6));
  assert(std::get<0>(std::get<0>(t7)) == 1);
  assert(std::get<1>(std::get<0>(t7)) == 2);
  assert(std::get<2>(std::get<0>(t7)) == 3);

  assert(std::get<0>(std::get<1>(t7)) == 4);
  assert(std::get<1>(std::get<1>(t7)) == 5);
  assert(std::get<2>(std::get<1>(t7)) == 6);

  return 0;
}

