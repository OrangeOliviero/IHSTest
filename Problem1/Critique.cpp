// The below code has been copied from the problem statement and annotated with the critique
// Critiques are prefixed with C[X], where X is a positive integer (e.g. C1)

// Will find the address of the company with the given name.
string FindAddress( list<Company> companies, string name )
// C1: The return type of `string` will create a new string object and copy the address into it
//     If this will be used frequently and the address will not (usually) be modified, it may
//      be worth returning a `const string&` instead. (Callers that do want to modify the string
//      can always assign the return to a non-const& string to copy it anyways.)
// C2: The company list is being passed by value. This is highly inefficient, especially if the
//      list is large (presumably we can expect this to be so), and it is likely that this is
//      the primary source of the observed slowness of this function.
//     Possible ways to improve this:
//      - Pass by `const&`
//        - The list will not be copied, and `const`-ness will ensure it is not modified (modulu const-casts)
//      - Use `std::move()` to move it into a local copy, have all callers std::move() the
//        list being passed in
//     Since this method does not modify the list, nor take ownership of it, std::move()
//      is likely the wrong choice
// C3: The `name` parameter is also passed-by-value, but is not modified. Similar to C1,
//      we can avoid the unnecessary create-and-copy of the string by using `const string&`.
//     Unlike C1, there is no good reason to *not* do this here.
//     This is unlikely to be the cause of poor performance unless this method is frequently called.
{
  for( list<Company>::iterator i = companies.begin(); i != companies.end(); i++ )
  // C4: The terminating condition `i != companies.end()` is called every iteration of the loop.
  //     This results in a function call (`companies.end()`) with every iteration of the loop.
  //     Since the loop is not modified, this function result will be un-changing, and can be
  //      cached in a local variable.
  // C5: The post-increment of the iterator results in the creation of a temporary that is
  //      not used. Using pre-increment (`++i`) would save the time to create and destroy
  //      that temporary.
  //     Some compilers *may* be able to recognize this and optimize away the creation of the
  //      temporary, but at best it can only make it equivalent to `++i`. If performance is
  //      a concern, `++i` should be used.
  {
    if( *i == name )
    {
      return (*i).address;
    }
  }
  return "";
  // C6: You can return {} here to directly create a default-constructed return object,
  //      rather than constructing it from an empty string.
}

// C7: Not specific to this particular method, however using a `list` to store this type
//      of data is generally quite ineffecient. The best search time is linear, so for
//      large N this can be quite time-consuming even when optimized.
//     In addition, since a list is (usually) connected via pointers to non-contiguous blocks
//      of memory, the machine architecture itself is not able to make use of its memory
//      cacheing tricks.
//     A `vector` would save the latter concern (and bring in its own issues), and a data type
//      with inherent sorting (such as a `set`) would allow faster searching for results.
//     A hash `map` using a specific, unique key (such as company name, potentially), would
//      allow for O(1) searches/additions of the companies.
