#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <trajcomp/trajcomp.hpp>
#include <trajcomp/bloomfilter.hpp>

#define MODULE_NAME trajcomp
namespace py = boost::python;

namespace trajcomp{ namespace python{
    
typedef size_t bloom_d_type;
typedef trajcomp::bloom::BloomFilter<bloom_d_type> BF;
typedef std::vector< bloom_d_type > bloom_filter_type;

struct bf_pickle_suite : py::pickle_suite {
  static py::tuple getinitargs(const BF& bf) {
    return py::make_tuple(bf.d, bf.fsize);
  }
  
  static py::tuple getstate(const BF& bf) {
    return py::make_tuple(bf.filter, bf.d, bf.fsize, bf.numElements);
  }

  static void setstate(BF& bf, py::tuple state) {
    /* no need for error handling here :o) 
    if (len(state) != 4)
    {
      PyErr_SetObject(PyExc_ValueError,
                          ("expected 4-item tuple in call to __setstate__; got %s"
                           % state).ptr());
      py::throw_error_already_set();
    }
    */
    bloom_filter_type filter = py::extract<bloom_filter_type>(state[0]);
    int d = py::extract<int>(state[1]);
    size_t fsize = py::extract<size_t>(state[2]);
    unsigned int numElements = py::extract<unsigned int>(state[3]);
    
    bf.configure(d, fsize);
    bf.filter = filter;
    bf.numElements = numElements;
  }
};

// pickling a c++ vector in boost python
// https://stackoverflow.com/questions/26762997/pickling-a-vector-in-boost-python
template <typename  T>
struct vector_pickle_suite: public py::pickle_suite
{
  static py::tuple getinitargs(const std::vector<T>& o){
    return py::make_tuple();
  }

  static py::tuple getstate(py::object obj){
    const std::vector<T>& o = py::extract<const std::vector<T>&>(obj)();
    return py::make_tuple(py::list(o));
  }

  static void setstate(py::object obj, py::tuple state){
    std::vector<T>& o = py::extract<std::vector<T>&>(obj)();
    py::stl_input_iterator<typename std::vector<T>::value_type> begin(state[0]), end;
    o.insert(o.begin(),begin,end);
  }
};


}//ns python
}//ns trajcomp


BOOST_PYTHON_MODULE(MODULE_NAME)
{
  namespace tp = trajcomp::python;
  
  py::class_<tp::bloom_filter_type>("bloom_filter_type")
    .def(py::vector_indexing_suite< tp::bloom_filter_type >())
    .def_pickle(tp::vector_pickle_suite<tp::bloom_d_type>());
  
  py::class_<tp::BF, boost::shared_ptr<tp::BF>, boost::noncopyable>("BloomFilter")
    .def(py::init<unsigned int, unsigned int>())
    .def(py::init<>())
    .def("configure", &tp::BF::configure)
    .def("summary", &tp::BF::summary)
    .def("dump", &tp::BF::dump)
    .def("empty", &tp::BF::empty)
    .def("subset", &tp::BF::subset)
    .def("resize", &tp::BF::resize)
    .def("foz", &tp::BF::foz)
    .def("esize", &tp::BF::esize)
    .def("eUnion", &tp::BF::eUnion)
    .def("eIntersect", &tp::BF::eIntersect)
    .def("contains", &tp::BF::contains_byval)
    .def("add", &tp::BF::add_byval)
    .def_pickle(tp::bf_pickle_suite());
    
}

