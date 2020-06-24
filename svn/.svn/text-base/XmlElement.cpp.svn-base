#include "XmlElement.hpp"
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;

namespace svnk {
namespace svn {

std::string XmlElement::GetName() const
{
  return XMLString::transcode(mElement->getTagName());
}

XmlElement XmlElement::GetChild(const std::string& name) const
{
  XmlElement::XmlElementList list = GetChildren(name);

  if(list.empty())
  {
    throw std::logic_error("No children with the name '" + name + "'");
  }
  
  return list.at(0);
}

XmlElement::XmlElementList XmlElement::GetChildren(const std::string& name) const
{
  DOMNodeList* list_of_childs = 
    mElement->getElementsByTagName(XMLString::transcode(name.c_str()));
  
  XmlElement::XmlElementList children;
  for(XMLSize_t i = 0; i < list_of_childs->getLength(); i++)
  {
    DOMElement* child = dynamic_cast<DOMElement*>(list_of_childs->item(i));
    children.push_back(XmlElement(child));
  }
  
  return children;
}

bool XmlElement::HasAttribute(const std::string& name) const
{
  return mElement->hasAttribute(XMLString::transcode(name.c_str()));
}


template <> 
bool XmlElement::GetAttributeAs(const std::string& name) const
{
  std::string arg = GetAttributeAs<std::string>(name);

  if(arg == "true")
  {
    return "true";
  }
  else if(arg == "false")
  {
    return false;
  }
  else
  {
    throw std::logic_error("Bad cast");
  }
}

std::string XmlElement::GetDestinationValue(const std::string& name) const
{
  if(name != "")
  {
    DOMNode *child = 
      mElement->getElementsByTagName(XMLString::transcode(name.c_str()))->item(0);
    return XMLString::transcode(child->getTextContent());
  }
  else
  {
    return XMLString::transcode(mElement->getTextContent());
  }
}

}}
