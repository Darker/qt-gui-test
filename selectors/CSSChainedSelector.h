#ifndef CSSCHAINEDSELECTOR_H
#define CSSCHAINEDSELECTOR_H
#include "Selector.h"
#include <QList>
class CssSelector;
typedef std::shared_ptr<CssSelector> CssSelectorPtr;

class CSSChainedSelector : public Selector
{
public:
  CSSChainedSelector();
  virtual QObjectList find(QObject* parent, bool returnFirst, QObjectList& targetList) override;
  virtual bool satisfies(QObject* object, TestingModule* module) const override;
  virtual QString parse(const QString&) override;
protected:
  QList<CssSelectorPtr> chain_;
  virtual QObjectList find(QObject* parent, bool returnFirst, QObjectList& targetList, const int currentSelector);
};

#endif // CSSCHAINEDSELECTOR_H
