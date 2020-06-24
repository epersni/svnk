#ifndef SVNK_SVN_XMLELEMENT_HPP
#define SVNK_SVN_XMLELEMENT_HPP

#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <string>
#include <vector>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/XMLString.hpp>

namespace svnk {
namespace svn {

class XmlElement
{
  public:
    XmlElement(const xercesc::DOMElement* element)
      : mElement(element) {}
    
    typedef std::vector<XmlElement> XmlElementList;
   
    std::string GetName() const;
    XmlElement GetChild(const std::string& name) const;
    XmlElementList GetChildren(const std::string& name) const;
    bool HasAttribute(const std::string& name) const;
 //   bool HasChild(const std::string name) const;
 //   
    template <typename T>
    T GetAttributeAs(const std::string& name) const
    {
      using namespace xercesc;
      if(!HasAttribute(name))
      {
        throw std::logic_error("No such attribute, '" + name + "'");
      }

      const XMLCh* attribute = 
        mElement->getAttribute(XMLString::transcode(name.c_str()));

      return boost::lexical_cast<T>(
          static_cast<char*>(XMLString::transcode(attribute)));
    }
    
    std::string GetDestinationValue(const std::string& name = "") const;

  private:
    const xercesc::DOMElement* mElement;

};

template <> bool XmlElement::GetAttributeAs(const std::string& name) const;

}}

#endif
