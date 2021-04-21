1. 继承QObject之后，还需要在类中增加 Q_OBJECT ，否则会报如下错误：

   ```
   static assertion failed: No Q_OBJECT in the class with the signal
   ```

   