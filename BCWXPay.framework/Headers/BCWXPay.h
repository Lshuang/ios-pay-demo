//
//  BCWXPay.h
//  BCWXPay
//
//  Created by RInz on 15/3/5.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>

//! Project version number for BCWXPay.
FOUNDATION_EXPORT double BCWXPayVersionNumber;

//! Project version string for BCWXPay.
FOUNDATION_EXPORT const unsigned char BCWXPayVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <BCWXPay/PublicHeader.h>


@interface BCWXPay : NSObject

#pragma mark - WXPay functions
/** @name WeChatPay */

/**
 * 处理微信通过URL启动App时传递的数据
 *
 * @param 需要在application:openURL:sourceApplication:annotation:中调用。
 * @param url 启动第三方应用时传递过来的URL
 * @param block  支付结果回调 Block，保证跳转支付过程中，当app被kill掉时，能通过这个接口得到支付结果
 * @return 成功返回YES，失败返回NO。
 */
+ (BOOL)handleOpenUrl:(NSURL *)url;

/**
 *  微信支付调用接口.初始化boby,totalFee,outTradeNo,traceid后调用此接口发起微信支付，并跳转到微信。
 *  如果您申请的是新版本(V3)的微信支付，请使用此接口发起微信支付.
 *  您在BeeCloud控制台需要填写“微信Partner ID”、“微信Partner KEY”、“微信APP ID”.
 *
 *  @param body       商品描述
 *  @param totalFee   支付金额,以分为单位
 *  @param outTradeNo 商户系统内部的订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param traceId    支付用户ID，必须保证在商户系统中唯一
 *  @param optional   扩展参数，可以传入任意数量的key/value对来补充对业务逻辑的需求
 *  @param block      支付结果回调
 */
+ (void)reqWXPayV3:(NSString *)body
          totalFee:(NSString *)totalFee
        outTradeNo:(NSString *)outTradeNo
           traceID:(NSString *)traceId
          optional:(NSDictionary *)optional
          payBlock:(BCPayBlock)block;

/**
 *  根据out_trade_no，out_refund_no, refundReason,refundFee查询订单是否可退款，允许退款情况下自动生成预退款订单，否则返回不可退款原因。预退款订单生成成功后，在BeeCloud商户后台对预退款订单进行处理。
 *
 *  @param outTradeNo   商户系统内部的支付订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param outRefundNo  商户系统内部的退款订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param refundReason 用户退款理由
 *  @param refundFee    用户欲退款金额，以分为单位
 *  @param block        退款结果回调.如果预退款成功,success=YES;失败success=NO.
 */
+ (void)reqWXRefundV3:(NSString *)outTradeNo
          outRefundNo:(NSString *)outRefundNo
         refundReason:(NSString *)refundReason
            refundFee:(NSString *)refundFee
             payBlock:(BCPayBlock)block;

/**
 *  根据商户自定义退款订单号查询退款状态。
 *
 *  @param out_refund_no 商户自定义退款订单号
 *  @param block         退款状态回调。success=YES时，正确返回从微信后台获取的退款状态;success=NO时，返回退款查询请求失败原因。
 */
+ (void)reqQueryRefund:(NSString *)out_refund_no block:(BCPayBlock)block;

/**
 *  同步查询支付订单或退款订单。内置购买只支持查询支付订单表。
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param type  支付平台的支付订单或者退款订单。
 *
 *  @return 符合条件的订单列表
 */
+ (NSArray *)queryWXPayOrderByKey:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type;

/**
 *  异步查询支付订单或退款订单。内置购买只支持查询支付订单表。
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param type  支付平台的支付订单或者退款订单
 *  @param block 接收查询结果
 */
+ (void)queryWXPayOrderByKeyAsync:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type block:(BCArrayResultBlock)block;

@end