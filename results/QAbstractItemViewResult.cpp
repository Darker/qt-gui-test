#include "QAbstractItemViewResult.h"
#include <QModelIndex>
#include <QAbstractItemModel>

QModelIndex findIndexByString(const QAbstractItemModel* model, const QString& text,  const QModelIndex& parent = QModelIndex());
QModelIndex findIndexByString(const QModelIndex& index, const QString& text) {
    // First check this particular index
    if(index.data().toString() == text)
        return index;
    // Check if it has children and loop
    const QAbstractItemModel* model = index.model();
    if(model==nullptr)
        return QModelIndex();
    if (!model->hasChildren(index))
        return QModelIndex();
    return findIndexByString(model, text, index);
}
QModelIndex findIndexByString(const QAbstractItemModel* model, const QString& text,  const QModelIndex& parent) {
    int rows = model->rowCount(parent);
    int cols = model->columnCount(parent);
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        QModelIndex index_child = findIndexByString(model->index(i, j, parent), text);
        if(index_child.isValid())
            return index_child;
      }
    return QModelIndex();
}
QModelIndex findIndexByString(const QAbstractItemView* view, const QString& text) {
    //const QModelIndex root = view->rootIndex();
    const QAbstractItemModel* model = view->model();
    return findIndexByString(model, text);
}

QAbstractItemViewResult::QAbstractItemViewResult(QAbstractItemView*i, TestingModule*m)
 : WidgetResult(i, m)
 , targetView_(i)
{

}

void QAbstractItemViewResult::doubleClickItem(const QString& name)
{
    QModelIndex index(findIndexByString(targetView_, name));
    //QString indexData = index.data().toString();
    if(index.isValid()) {
        targetView_->doubleClicked(index);
    }
}




void QAbstractItemViewResult::selectItems(const QStringList& list)
{
    if(list.size() > 0) {
        QModelIndex index(findIndexByString(targetView_, list[0]));
        //QString indexData = index.data().toString();
        if(index.isValid()) {
            targetView_->clicked(index);
        }
    }
}
