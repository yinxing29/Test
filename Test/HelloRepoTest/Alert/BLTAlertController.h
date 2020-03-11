//
//  BLTAlertController.h
//  BLTUIKit
//
//  Created by liu bin on 2020/2/26.
//  Copyright © 2020 liu bin. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BLTAlertAction.h"
#import "BLTTextFieldView.h"


typedef NS_ENUM(NSInteger, BLTAlertControllerStyle){
    BLTAlertControllerStyleAlert = 0,   //文案类的展示
    BLTAlertControllerStyleActionSheet, //actionSheet样式的
    BLTAlertControllerStyleFeedAlert,   //反馈类弹框
};

@interface BLTAlertController : UIViewController


/**
 @param title alert的title  系统API方式创建的方法
 @param message message 小于两行居中显示  大于两行靠左显示
 @param style 是alert 还是 actionSheet
 */
+ (instancetype)alertControllerWithTitle:(NSString *)title mesage:(NSString *)message style:(BLTAlertControllerStyle)style;

/** 快速初始化的 */
- (instancetype)initWithTitle:(NSString *)title mesage:(NSString *)message style:(BLTAlertControllerStyle)style sureTitle:(NSString *)sureTitle sureBlock:(void(^)(BLTAlertAction *cancelAction))sureBlock;
/** 快速初始化取消  确定按钮的 */
- (instancetype)initWithTitle:(NSString *)title mesage:(NSString *)message style:(BLTAlertControllerStyle)style cancelTitle:(NSString *)cancelTitle cancelBlock:(void(^)(BLTAlertAction *cancelAction))cancelBlock sureTitle:(NSString *)sureTitle sureBlock:(void(^)(BLTAlertAction *sureAction))sureBlock;

- (void)addAction:(BLTAlertAction *)action;

/** 添加textField */
- (void)addTextFieldWithConfigurationHandler:(void(^)(BLTTextFieldView *textView))configurationHandler;

/** alert的内容view自定义 */
- (void)addCustomView:(UIView *)customView;

- (void)showWithAnimated:(BOOL)showAnimated;

- (void)dismissWithAnimated:(BOOL)dismissAnimated;

@property (nonatomic, copy, readonly) NSArray<UIAlertAction *> *actions;

/** 圆角的大小 */
@property (nonatomic, assign) CGFloat alertContentRaduis;

/** 按钮的高度 */
@property (nonatomic, assign) CGFloat alertButtonHeight;

/** alert距屏幕的间距 */
@property (nonatomic, assign) UIEdgeInsets alertContentInsets;

/** 最大的内容的宽度 */
@property (nonatomic, assign) CGFloat alertContentMaxWidth;

/** title 文字的样式  间距 字体  颜色 等 */
@property (nonatomic, copy) NSDictionary <NSString *, id>*alertTitleAttributes;

@property (nonatomic, copy) NSDictionary <NSString *, id>*alertContentAttributes;

/** 内容设置富文本 设置了富文本一些默认设置的就无效了 需要自己设置富文本的样式 */
@property (nonatomic, copy) NSAttributedString *alertContentAttributeString;

/** 给内容添加富文本的点击事件 配合alertContentAttributeString 使用*/
- (void)addContentAttributeTapActionWithStrings:(NSArray <NSString *>*)strings tapHandler:(void(^)(NSString *string, NSRange range, NSInteger index))tapHandler;

@property (nonatomic, strong) UIColor *alertSeparatorColor;

/** 设置正常按钮的attributes */
@property (nonatomic, copy) NSDictionary <NSString *, id>*alertButtonAttributes;
/** 设置取消按钮的attibutes */
@property (nonatomic, copy) NSDictionary <NSString *, id>*alertCancelButtonAttributes;
/** 设置destructive的样式 */
@property (nonatomic, copy) NSDictionary <NSString *, id>*alertDestructiveButtonAttributes;

/** 弹框北京遮罩的颜色 */
@property (nonatomic, strong) UIColor *alertMaskViewBackgroundColor;
/** 非按钮部分的背景色 */
@property (nonatomic, strong) UIColor *alertHeaderBackgroundColor;
/** 按钮的背景色  默认和alertHeaderBackgroundColor一致 */
@property (nonatomic, strong) UIColor *alertButtonBackgroundColor;
/** 非按钮部分的内间距 */
@property (nonatomic, assign) UIEdgeInsets alertHeaderInsets;
/** title和content的间距 */
@property (nonatomic, assign) CGFloat alertTitleContentSpacing;

/** textField的font */
@property (nonatomic, strong) UIFont *alertTextFieldFont;
@property (nonatomic, strong) UIColor *alertTextFieldTextColor;
@property (nonatomic, assign) CGFloat alertTextFieldHeight;

/** 按钮的排序是否遵守添加的  默认为NO  和系统保持一致 */
@property (nonatomic, assign) BOOL orderAlertActionsByAddOrdered;

/** 在title上面加一个图片 */
- (void)addTitleImage:(UIImage *)titleImage;
/** 和上面的配对使用 默认15*/
@property (nonatomic, assign) CGFloat alertTitleImageSpacing;

#pragma mark - actionSheet的属性设置
@property (nonatomic, assign) CGFloat actionSheetContentMaxWidth;

@property (nonatomic, assign) CGFloat actionSheetContentCornerRaduis;
/** 取消按钮的间距 */
@property (nonatomic, assign) CGFloat actionSheetCancelButtonSpacing;
/** 按钮的高度 默认55 */
@property (nonatomic, assign) CGFloat actionSheetButtonHeight;

#pragma mark - feedAlert
/** 右上角关闭按钮的 */
- (void)addRightTopCloseButtonHandler:(dispatch_block_t)handler;

@property (nonatomic, assign) CGFloat feedAlertButtonHoriSpacing;

@property (nonatomic, assign) CGFloat feedAlertButtonVerticalSpacing;

@property (nonatomic, strong) UIColor *feedAlertStartGradientColor;

@property (nonatomic, strong) UIColor *feedAlertEndGradientColor;

/** 按钮距离弹框的内间距 */
@property (nonatomic, assign) UIEdgeInsets feedAlertButtonInsets;

/** feedAlert按钮样式的属性 */
@property (nonatomic, copy) NSDictionary <NSString *, id>*feedAlertButtonAttributes;
/** feedAlert按钮的样式 */
@property (nonatomic, copy) NSDictionary <NSString *, id> *feedAlertDestrutiveButtonAttributes;

+ (BOOL)isAnyAlertControllerExist;

@end


/** 全局样式统一设置的 */
@interface BLTAlertController (Appearance)

+ (instancetype)appearance;

@end


