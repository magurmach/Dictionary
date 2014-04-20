#Dictionary and Priority Queue for OGDF

##Introduction
This project aims Search Trees and Priority Queues implementation for OGDF. At the completion there will be implementation of `template <class Key, class Data, class Module > class Dictionary` and `template <class Key, class Container, class Comparer > class PriorityQueue` where detailed description will be available below.

##Dictionary

`Dictionary` is a standard implementation of dictionary class.

`template <class Key, class Data, class Module > class Dictionary`

###Key:
`class Key` need to have operators: `<` and `==`
###Data:
`class Data` to define type of data to be stored against key
###Module:
Any data structure class with `insert`, `remove`, `find` function and sub class `iterator` can be used as Module

