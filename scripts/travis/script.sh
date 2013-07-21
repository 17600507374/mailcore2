#!/bin/sh
set -e

xcodebuild -list -project build-mac/mailcore2.xcodeproj

xcodebuild -project build-mac/mailcore2.xcodeproj -sdk iphoneos6.1 -target "static mailcore2 ios" build
xcodebuild -project build-mac/mailcore2.xcodeproj -sdk iphonesimulator6.1 -target "static mailcore2 ios" build
xcodebuild -project build-mac/mailcore2.xcodeproj -sdk iphoneos6.1 -target "test-ios" build
xcodebuild -project build-mac/mailcore2.xcodeproj -sdk iphonesimulator6.1 -target "test-ios" build

xcodebuild -project build-mac/mailcore2.xcodeproj -sdk macosx10.8 -target "static mailcore2 osx" build
xcodebuild -project build-mac/mailcore2.xcodeproj -sdk macosx10.8 -target "tests" build

#xctool -project build-mac/mailcore2.xcodeproj -scheme "static mailcore2 ios" build
#xctool -project build-mac/mailcore2.xcodeproj -scheme "static mailcore2 osx" build
