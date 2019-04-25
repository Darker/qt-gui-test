#include "AddChildEventFilterCSS.h"
#include "selectors/CSSChainedSelector.h"
#include <QDialog>
AddChildEventFilterCSS::AddChildEventFilterCSS(const QString& selectorStr, QObject *parent)
    : AddChildEventFilter(parent)
    , selector(nullptr)
{
    selector.reset(new CSSChainedSelector());
    selector->parse(selectorStr);
    selector = selector->optimize(selector);
}

void AddChildEventFilterCSS::reportChildAdded(QObject* child, QObject* parent)
{
	if (QDialog* dialog = qobject_cast<QDialog*>(child)) {
		dialog->accept();
	}
    if(selector->satisfies(child, nullptr)) {
        AddChildEventFilter::reportChildAdded(child, parent);
    }
	else {
		const QObjectList& children = child->children();
		Q_FOREACH(QObject* childChild, children) {
			if (selector->satisfies(childChild, nullptr))
				AddChildEventFilter::reportChildAdded(childChild, child);
		}
	}
}
