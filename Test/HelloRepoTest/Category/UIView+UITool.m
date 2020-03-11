//
//  UIView+UITool.m
//  BLTUIKit
//
//  Created by liu bin on 2020/2/26.
//  Copyright © 2020 liu bin. All rights reserved.
//

#import "UIView+UITool.h"
#import "BLTUICommonDefines.h"
#import <objc/runtime.h>

const CGFloat BLTUIViewSelfSizingHeight = INFINITY;

@implementation UIView (UITool)

+ (void)load{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        swizzleInstanceMethod([UIView class], @selector(setFrame:), @selector(BLT_setFrame:));
    });
}

- (void)BLT_setFrame:(CGRect)frame{
    if (CGRectGetWidth(frame) > 0 && isinf(frame.size.height)){
        CGSize size = [self sizeThatFits:CGSizeMake(CGRectGetWidth(frame), CGFLOAT_MAX)];
        frame = CGRectSetHeight(frame, size.height);
    }
    [self BLT_setFrame:frame];
}

- (void)setLayerCornerRaduis:(CGFloat)layerCornerRaduis{
    self.layer.cornerRadius = layerCornerRaduis;
    self.layer.masksToBounds = YES;
    objc_setAssociatedObject(self, @selector(layerCornerRaduis), [NSNumber numberWithFloat:layerCornerRaduis], OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)layerCornerRaduis{
    return [objc_getAssociatedObject(self, _cmd) floatValue];
}

/** 显示圆角的 */
- (void)showLayerCorner:(UIRectCorner)rectCorner size:(CGSize)size lineWidth:(CGFloat)lineWidth{
    CAShapeLayer *maskLayer = objc_getAssociatedObject(self, @selector(showLayerCorner:size:lineWidth:));
    if (maskLayer) {
        return;
    }
    UIBezierPath *bezierPath = [UIBezierPath bezierPathWithRoundedRect:self.bounds byRoundingCorners:rectCorner cornerRadii:size];
    maskLayer = [[CAShapeLayer alloc] init];
    maskLayer.frame = self.bounds;
    maskLayer.path = bezierPath.CGPath;
    self.layer.mask = maskLayer;
    objc_setAssociatedObject(self, @selector(showLayerCorner:size:lineWidth:), maskLayer, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)showBorderColor:(UIColor *)color cornerRaduis:(CGFloat)cornerRaduis borderWidth:(CGFloat)borderWidth{
    self.layer.borderColor = color.CGColor;
    self.layer.cornerRadius = cornerRaduis;
    self.layer.borderWidth = borderWidth;
}

/** 给view添加线 */
- (void)addLineRectCorner:(UIRectLineSide)rectCorner lineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor{
    BOOL hasAddLine = [objc_getAssociatedObject(self, @selector(addLineRectCorner:lineWidth:lineColor:)) boolValue];
    if (hasAddLine) {
        return;
    }
    CAShapeLayer *lineLayer = [[CAShapeLayer alloc] init];
    lineLayer.strokeColor = lineColor.CGColor;
    lineLayer.lineWidth = lineWidth;
    [self.layer addSublayer:lineLayer];
    
    UIBezierPath *bezierPath = [[UIBezierPath alloc] init];
    if (rectCorner & UIRectLineSideLeft) {
        [bezierPath moveToPoint:CGPointMake(0, 0)];
        [bezierPath addLineToPoint:CGPointMake(0, CGRectGetHeight(self.frame))];
    }
    
    if (rectCorner & UIRectLineSideTop) {
        [bezierPath moveToPoint:CGPointMake(0, 0)];
        [bezierPath addLineToPoint:CGPointMake(CGRectGetWidth(self.frame), 0)];
    }
    
    if (rectCorner & UIRectLineSideRight) {
        [bezierPath moveToPoint:CGPointMake(CGRectGetWidth(self.frame), 0)];
        [bezierPath addLineToPoint:CGPointMake(CGRectGetWidth(self.frame), CGRectGetHeight(self.frame))];
    }
    
    if (rectCorner & UIRectLineSideBottom) {
        [bezierPath moveToPoint:CGPointMake(0, CGRectGetHeight(self.frame))];
        [bezierPath addLineToPoint:CGPointMake(CGRectGetWidth(self.frame), CGRectGetHeight(self.frame))];
    }
    
    lineLayer.path = bezierPath.CGPath;
    objc_setAssociatedObject(self, @selector(addLineRectCorner:lineWidth:lineColor:), @(YES), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

/** 添加渐变色 */
- (void)addGrandientLayerStartColor:(UIColor *)startColor endColor:(UIColor *)endColor direction:(BLTGrandientLayerDirection)direction{
    CAGradientLayer *gradientLayer = objc_getAssociatedObject(self, @selector(addGrandientLayerStartColor:endColor:direction:));
    if (gradientLayer) {
        return;
    }
    gradientLayer = [[CAGradientLayer alloc] init];
    gradientLayer.frame = self.bounds;
    [gradientLayer setColors:@[(id)startColor.CGColor,(id)endColor.CGColor]];
    [gradientLayer setStartPoint:CGPointZero];
    CGPoint endPoint = CGPointZero;
    switch (direction) {
        case BLTGrandientLayerDirectionLeftToRight:
            endPoint = CGPointMake(1.0, 0);
            break;
        case BLTGrandientLayerDirectionLeftToRightBotton:
            endPoint = CGPointMake(1.0, 1.0);
            break;
        case BLTGrandientLayerDirectionTopToBottom:
            endPoint = CGPointMake(0, 1.0);
            break;
        default:
            break;
    }
    [gradientLayer setEndPoint:endPoint];
    objc_setAssociatedObject(self, @selector(addGrandientLayerStartColor:endColor:direction:), gradientLayer, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    [self.layer addSublayer:gradientLayer];
    [self.layer insertSublayer:gradientLayer atIndex:0];
}

@end
