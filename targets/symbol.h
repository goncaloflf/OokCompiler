// $Id: symbol.h,v 1.2 2016/06/24 12:55:28 ist13500 Exp $ -*- c++ -*-
#ifndef __OOK_SEMANTICS_SYMBOL_H__
#define __OOK_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace ook {

    class symbol {
      const basic_type *_type;
      std::string _name;
      long _value; // hack!

    public:
      inline symbol(const basic_type *type, const std::string &name, long value) :
          _type(type), _name(name), _value(value) {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline const basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline long value() const {
        return _value;
      }
      inline long value(long v) {
        return _value = v;
      }
    };

} // ook

#endif
