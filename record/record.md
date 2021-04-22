1. 继承QObject之后，还需要在类中增加 Q_OBJECT ，否则会报如下错误：

   ```
   static assertion failed: No Q_OBJECT in the class with the signal
   ```

2.  QT槽的命名规则

   ```
   QT默认指定的槽的命名规则为 on_<name_of_object>_<action>，所以如果出现自定义的槽函数有着一样的命名规则，那么就会出现如下警告:QMetaObject::connectSlotsByName: No matching signal
   ```

   