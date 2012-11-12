//down
#include "tab.h"
#include <QSizePolicy>


Tab::Tab(QWidget *parent) : QTabWidget(parent) {
    defaultList = new List(this);

    setTabsClosable (false);
    setTabShape (QTabWidget::Rounded);
    setFocusPolicy (Qt::NoFocus);
    setStyleSheet (
                "QTabWidget::pane {border-top: 1px solid #C2C7CB;}"
                "QTabWidget::tab-bar { left: 5px; }"
                );

    addTab (defaultList, tr("播放列表"));
    setCurrentWidget (defaultList);
    setSizePolicy (QSizePolicy::Expanding,QSizePolicy::Expanding);
    defaultList->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}


List * Tab::getList(int id) {
    switch(id) {
    case 1:
        return NULL;
    default :
        return defaultList;
    }
}
