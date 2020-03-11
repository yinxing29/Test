//
//  BLTUICommonDefines.h
//  BLTUIKit
//
//  Created by liu bin on 2020/2/26.
//  Copyright © 2020 liu bin. All rights reserved.
//

/**  一些UI常用的方法   */
#ifndef BLTUICommonDefines_h
#define BLTUICommonDefines_h
#import <objc/runtime.h>

#define BLT_DEF_SCREEN_HEIGHT [[UIScreen mainScreen] bounds].size.height

#define BLT_DEF_SCREEN_SIZE   [[UIScreen mainScreen] bounds].size

#define BLT_IS_IPHONEX      ([[UIApplication sharedApplication] statusBarFrame].size.height == 44)

#define BLT_IPHONEX_MARGIN_TOP       44
#define BLT_IPHONEX_MARGIN_BOTTOM      34

#define BLT_SCREEN_BOTTOM_OFFSET (BLT_IS_IPHONEX ? BLT_IPHONEX_MARGIN_BOTTOM : 0)
#define BLT_SCREEN_TOP_OFFSET (BLT_IS_IPHONEX ? BLT_IPHONEX_MARGIN_TOP : 0)
#define BLT_SCREEN_NAVI_HEIGHT (BLT_IS_IPHONEX ? BLT_IPHONEX_MARGIN_TOP + 44 : 64)

#define BLTHEXCOLOR(rgbValue)                                                                                             \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16)) / 255.0                                               \
green:((float)((rgbValue & 0xFF00) >> 8)) / 255.0                                                  \
blue:((float)(rgbValue & 0xFF)) / 255.0                                                           \
alpha:1.0]

CG_INLINE void swizzleInstanceMethod(Class cls, SEL originSelector, SEL swizzleSelector){
    if (!cls) {
        return;
    }
    /* if current class not exist selector, then get super*/
    Method originalMethod = class_getInstanceMethod(cls, originSelector);
    Method swizzledMethod = class_getInstanceMethod(cls, swizzleSelector);
    
    /* add selector if not exist, implement append with method */
    if (class_addMethod(cls,
                        originSelector,
                        method_getImplementation(swizzledMethod),
                        method_getTypeEncoding(swizzledMethod)) ) {
        /* replace class instance method, added if selector not exist */
        /* for class cluster , it always add new selector here */
        class_replaceMethod(cls,
                            swizzleSelector,
                            method_getImplementation(originalMethod),
                            method_getTypeEncoding(originalMethod));
        
    } else {
        /* swizzleMethod maybe belong to super */
        class_replaceMethod(cls,
                            swizzleSelector,
                            class_replaceMethod(cls,
                                                originSelector,
                                                method_getImplementation(swizzledMethod),
                                                method_getTypeEncoding(swizzledMethod)),
                            method_getTypeEncoding(originalMethod));
    }
}



#pragma mark - 字体
CG_INLINE UIFont *UIFontPFFontSize(CGFloat x){
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Regular" size:x] ? [UIFont fontWithName:@"PingFangSC-Regular" size:x] : [UIFont systemFontOfSize:x];
    return font;
}

CG_INLINE UIFont *UIFontPFBoldFontSize(CGFloat x){
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Semibold" size:x] ? [UIFont fontWithName:@"PingFangSC-Semibold" size:x] : [UIFont boldSystemFontOfSize:x];
    return font;
}

CG_INLINE UIFont *UIFontPFMediumFontSize(CGFloat x){
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Medium" size:x] ? [UIFont fontWithName:@"PingFangSC-Medium" size:x] : [UIFont systemFontOfSize:x];
    return font;
}


/** 取UIEdgeInset的水平方向的值 */
CG_INLINE CGFloat UIEdgeInsetsGetHorizontalValue(UIEdgeInsets insets){
    return insets.left + insets.right;
}

/** 去UIEdgeInst竖直方向的值 */
CG_INLINE CGFloat UIEdgeInsetsGetVerticalValue(UIEdgeInsets insets){
    return insets.top + insets.bottom;
}

/** 根据Inset内间距返回一个新的Rect */
CG_INLINE CGRect CGRectFromUIEdgeInsets(CGRect frame, UIEdgeInsets insets){
    frame = CGRectMake(CGRectGetMinX(frame) + insets.left,
                       CGRectGetMinY(frame) + insets.top,
                       CGRectGetWidth(frame) - UIEdgeInsetsGetHorizontalValue(insets),
                       CGRectGetHeight(frame) - UIEdgeInsetsGetVerticalValue(insets));
    return frame;
}

/** 设置frame的宽度 */
CG_INLINE CGRect CGRectSetWidth(CGRect frame, CGFloat width){
    frame = CGRectMake(frame.origin.x, frame.origin.y, width, frame.size.width);
    return frame;
}

/** 设置frame的高度 */
CG_INLINE CGRect CGRectSetHeight(CGRect frame, CGFloat height){
    frame = CGRectMake(frame.origin.x, frame.origin.y, frame.size.width, height);
    return frame;
}

CG_INLINE CGRect CGRectSetX(CGRect frame, CGFloat x){
    frame = CGRectMake(x, frame.origin.y, frame.size.width, frame.size.height);
    return frame;
}

CG_INLINE CGRect CGRectSetY(CGRect frame, CGFloat y){
    frame = CGRectMake(frame.origin.x, y, frame.size.width, frame.size.height);
    return frame;
}

CG_INLINE UIImage * UIImageNamed(NSString *imageName){
    return [UIImage imageNamed:imageName];
}

CG_INLINE UIImage* UIImageNamedFromBundle(NSString *imageName){
    NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"BLTUIKit.bundle"];
    NSBundle *bundle = [NSBundle bundleWithPath:path];
    return [UIImage imageNamed:imageName inBundle:bundle compatibleWithTraitCollection:nil];
}

#endif /* BLTUICommonDefines_h */
