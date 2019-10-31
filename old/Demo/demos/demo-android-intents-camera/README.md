# Acquiring an image with Android Intents

* shows how to acquire an image using an Android Intent
* the images are stored under `Android/data/com.initiallights.demo_android_intents_camera/files/Pictures`
* on start, the app scans the above folder for existing files and allows the user to select any of the existing images

## Tips & Tricks

### Create custom Android templates

* expand the _Projects_ > _Build_ > _Build Steps_ > _Build Android APK_
* click the **Create Templates** button to create a custom `android/AndroidManifest.xml` and `android/gradle` files

### Configure the FileProvider

* in `android/AndroidManifest.xml`
  * request the camera feature
  * request `READ_EXTERNAL_STORAGE` and `WRITE_EXTERNAL_STORAGE` permissions
  * configure the `FileProvider`
* create `android/res/xml/file_paths.xml` and configure the `FileProvider` paths
* edit `build.gradle` and add `support-compat` libs to it
* if the `support-compat` libs are not present, use the _Android SDK Manager_ to download them

## References

* https://developer.android.com/training/camera/photobasics
* https://blog.qt.io/blog/2016/06/30/intents-with-qt-for-android-part-1/
