// From the personal library of Paul Ilardi (http://github.com/CodePi).
// Free to use or modify.

#pragma once

// Modified from boost::any
// Original http://www.boost.org/libs/any
// Modified by Paul Ilardi (http://github.com/CodePi)

// Changes:
// - Added toStream and toStreamContainer methods 
// - Added operator<< for AnyType
// - Added to<Type>() to convert contents to Type intelligently
// - Added to_i(), to_f(), to_s() to convert to int, double, and string respectively
// - Added getRef<Type>() as a wrapper for anyType_cast (throws if used improperly)
// - Added get<Type>() as a wrapper for anyType_cast (NULL if not valid)
// - Removed dependancy on other parts of boost
// - Renamed classes and functions to prevent collisions

#include <typeinfo>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <deque>

namespace codepi{

   class bad_anyType_cast : public std::bad_cast
   {
   public:
      virtual const char * what() const throw()
      {
         return "boost_mod::bad_anyType_cast: "
            "failed conversion using anyType_cast";
      }
   };

   class AnyType {
   public: 

      AnyType()       : content(0)
      {
      }

      template<typename ValueType>
      AnyType(const ValueType & value)
         : content(new holder<ValueType>(value))
      {
      }

      AnyType(const AnyType & other)
         : content(other.content ? other.content->clone() : 0)
      {
      }

      AnyType(const char* str)
         : content(new holder<std::string>(str))
      {
      }

      ~AnyType()
      {
         delete content;
      }

   public: // modifiers

      AnyType & swap(AnyType & rhs)
      {
         std::swap(content, rhs.content);
         return *this;
      }

      template<typename ValueType>
      AnyType & operator=(const ValueType & rhs)
      {
         AnyType(rhs).swap(*this);
         return *this;
      }

      AnyType & operator=(AnyType rhs)
      {
         rhs.swap(*this);
         return *this;
      }

   public: // queries

      bool empty() const
      {
         return !content;
      }

      const std::type_info & type() const
      {
         return content ? content->type() : typeid(void);
      }

      std::ostream& toStream(std::ostream& ss){
         if(!content) return ss;
         return content->toStream(ss);
      }

      template<typename T> T* get(); // implemented below 

      template<typename T>
      T& getRef(){ 
         // throws bad_anyType_cast if failed
         T* p = get<T>();
         if(!p) throw bad_anyType_cast();
         return *p;
      }      
      
      template<typename T>
      T to(){
         T* p = get<T>();
         if(p) return *p; //return if correct type
         else{ // try to convert otherwise
            std::stringstream ss;
            T val=T(); //returns default value if conversion fails
            if(content){
               content->toStream(ss);
               ss>>val;
            }
            return val;
         }
      }

      int to_i(){ return to<int>(); }
      double to_f(){ return to<double>(); }
      std::string to_s(){ return to<std::string>(); }

   private: // types

      class placeholder
      {
      public: // structors

         virtual ~placeholder()
         {
         }

      public: // queries

         virtual const std::type_info & type() const = 0;

         virtual placeholder * clone() const = 0;

         virtual std::ostream& toStream(std::ostream& ss)=0;

      };

      template<typename ValueType>
      class holder : public placeholder
      {
      public: // structors

         holder(const ValueType & value)
            : held(value)
         {
         }

         template <typename T>
         static std::ostream& toStreamContainer(std::ostream& ss, T& vec){
            int i=0;
            for(typename T::iterator e=vec.begin();e!=vec.end();e++){
               if(i>0) ss<<",";
               ss<<(*e);
               i++;
            }
            return ss;
         }

         template <typename T>
         static std::ostream& toStream(std::ostream& ss, std::vector<T>& vec){
            return toStreamContainer(ss,vec);
         }

         template <typename T>
         static std::ostream& toStream(std::ostream& ss, std::list<T>& vec){
            return toStreamContainer(ss,vec);
         }

         template <typename T>
         static std::ostream& toStream(std::ostream& ss, std::set<T>& vec){
            return toStreamContainer(ss,vec);
         }

         template <typename T>
         static std::ostream& toStream(std::ostream& ss, std::deque<T>& vec){
            return toStreamContainer(ss,vec);
         }

         template <typename T>
         static std::ostream& toStream(std::ostream& ss, T& val){
            ss<<val;
            return ss;
         }

         std::ostream& toStream(std::ostream& ss){
            toStream(ss,held);
            return ss;
         }

      public: // queries

         virtual const std::type_info & type() const
         {
            return typeid(ValueType);
         }

         virtual placeholder * clone() const
         {
            return new holder(held);
         }

      public: // representation

         ValueType held;

      private: // intentionally left unimplemented
         holder & operator=(const holder &);
      };

   private: // representation

      template<typename ValueType>
      friend ValueType * anyType_cast(AnyType *);

      placeholder * content;

   };

   template<typename ValueType>
   ValueType * anyType_cast(AnyType * operand)
   {
      return operand && 
         operand->type() == typeid(ValueType)
         ? &static_cast<AnyType::holder<ValueType> *>(operand->content)->held
         : 0;
   }

   template<typename ValueType>
   inline const ValueType * anyType_cast(const AnyType * operand)
   {
      return anyType_cast<ValueType>(const_cast<AnyType *>(operand));
   }

   template<typename T>
   T* AnyType::get(){ 
      return anyType_cast<T>(this);
   }


   inline std::ostream& operator<<(std::ostream& ss, AnyType& any){
      any.toStream(ss);
      return ss;
   }

   inline void swap(AnyType& a1, AnyType& a2){
      a1.swap(a2);
   }

}; //namespace codepi

// Original Boost::any Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
