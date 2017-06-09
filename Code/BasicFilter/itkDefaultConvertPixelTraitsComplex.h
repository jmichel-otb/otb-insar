#include "itkDefaultConvertPixelTraits.h"
#include <complex>

namespace itk
{
#define ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL(type)                      \
  template< >                                                              \
  class DefaultConvertPixelTraits< type >                                  \
  {                                                                        \
public:                                                                    \
    typedef type ComponentType;                                            \
    static unsigned int GetNumberOfComponents()                            \
      {                                                                    \
      return 1;                                                            \
      }                                                                    \
    static unsigned int GetNumberOfComponents(const type)                  \
      {                                                                    \
      return 1;                                                            \
      }                                                                    \
    static void SetNthComponent(int, type & pixel, const ComponentType &v) \
      {                                                                    \
      pixel = v;                                                           \
      }                                                                    \
    static type GetNthComponent(int, const type pixel)                     \
      {                                                                    \
      return pixel;                                                        \
      }                                                                    \
    static type GetScalarValue(const type &pixel)                          \
      {                                                                    \
      return pixel;                                                        \
      }                                                                    \
  };

ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL(std::complex<float>)
ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL(std::complex<double>)


#undef ITK_DEFAULTCONVERTTRAITS_NATIVE_SPECIAL

}; // End namespace ITK
