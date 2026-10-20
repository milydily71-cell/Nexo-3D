# Android native host

This module is a Java Activity + Android SurfaceView host. It passes the platform Surface to a JNI bridge and forwards resize/touch events. It contains no HTML, WebView, or browser-based editor.

The JNI bridge currently owns the native-window lifecycle and diagnostic logging. Vulkan swapchain creation and frame submission are still pending; therefore this host is the Android integration foundation, not yet a runnable 3D editor APK. Build/package integration and an actual render loop are follow-up milestones.
