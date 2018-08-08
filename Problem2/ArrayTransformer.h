#ifndef __ARRAYTRANSFORMER_H__
#define __ARRAYTRANSFORMER_H__

template<class Iterator, typename Type>
void transformArray(Iterator iterator, Iterator endIt, Type(*transform)(Type, Type, const Type*))
{
  if (iterator == endIt) return;

  Type prevValue = *iterator++;
  if (iterator == endIt) return;

  // Get our initial state and transform the first value
  Type prevResult = transform(*iterator, prevValue, nullptr);
  prevValue = *iterator;
  *iterator++ = prevResult;

  // Transform the rest of the container
  while (iterator != endIt) {
    prevResult = transform(*iterator, prevValue, &prevResult);
    prevValue = *iterator;
    *iterator++ = prevResult;
  }
}

template<typename Type>
Type sumPrev(Type current, Type previous, const Type* prevResult)
{
  if (!prevResult) {
    return current + previous;
  }
  return current + *prevResult;
}

template<typename Type>
Type mulPrev(Type current, Type previous, const Type* prevResult)
{
  if (!prevResult) {
    return current * previous;
  }
  return current * *prevResult;
}

template<typename Type>
Type deltaPrev(Type current, Type previous, const Type* prevResult)
{
  return current - previous;
}

#endif /* __ARRAYTRANSFORMER_H__ */
