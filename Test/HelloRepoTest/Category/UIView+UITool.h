//
//  UIView+UITool.h
//  BLTUIKit
//
//  Created by liu bin on 2020/2/26.
//  Copyright © 2020 liu bin. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_OPTIONS(NSUInteger, UIRectLineSide){
    UIRectLineSideLeft = 1 << 0,
    UIRectLineSideTop = 1 << 1,
    UIRectLineSideRight = 1 << 2,
    UIRectLineSideBottom = 1 << 3,
    UIRectLineSideAllSide = ~0UL
};

typedef NS_ENUM(NSInteger, BLTGrandientLayerDirection){
    BLTGrandientLayerDirectionLeftToRight = 0,
    BLTGrandientLayerDirectionLeftToRightBotton,
    BLTGrandientLayerDirectionTopToBottom,
};

extern const CGFloat BLTUIViewSelfSizingHeight;

@interface UIView (UITool)

@property (nonatomic, assign) CGFloat layerCornerRaduis;

/** 显示圆角的 */
- (void)showLayerCorner:(UIRectCorner)rectCorner size:(CGSize)size lineWidth:(CGFloat)lineWidth;
/** 显示边框的 */
- (void)showBorderColor:(UIColor *)color cornerRaduis:(CGFloat)cornerRaduis borderWidth:(CGFloat)borderWidth;

/** 给view添加线 */
- (void)addLineRectCorner:(UIRectLineSide)rectCorner lineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

/** 添加渐变色 */
- (void)addGrandientLayerStartColor:(UIColor *)startColor endColor:(UIColor *)endColor direction:(BLTGrandientLayerDirection)direction;

@end


