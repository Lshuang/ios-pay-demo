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
+ (BOOL)handleOpenUrl:(NSURL *)url withBlock:(BCPayBlock)block;

/**
 *  微信支付调用接口.初始化wx_boby,wx_totalFee,wx_outTradeNo,wx_traceid后调用此接口发起微信支付，并跳转到微信。
 *
 *  @param wx_body       商品描述
 *  @param wx_totalFee   支付金额,以分为单位
 *  @param wx_outTradeNo 商户系统内部的订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param wx_traceId    支付用户ID，必须保证在商户系统中唯一
 *  @param block         支付结果回调
 */
+ (void)reqWXPayment:(NSString *)wx_body
            totalFee:(NSString *)wx_totalFee
          outTradeNo:(NSString *)wx_outTradeNo
             traceID:(NSString *)wx_traceId
            optional:(NSMutableDictionary *)optional
            payBlock:(BCPayBlock)block;

/**
 *  根据商家提供的订单号，异步查询该订单状态是否支持退款。
 *
 *  @param wx_outTradeNo 商户系统内部的订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param block         如果支持退款，success=YES,strMsg=可退款金额；如果不支持退款，success=NO,strMsg=不支持退款原因。
 */
+ (void)canRefundForWeChatPay:(NSString *)wx_outTradeNo block:(BCPayBlock)block;

/**
 *  根据out_trade_no，out_refund_no, refundReason,refundFee查询订单是否可退款，允许退款情况下自动生成预退款订单，否则返回不可退款原因。预退款订单生成成功后，在BeeCloud商户后台对预退款订单进行处理。
 *
 *  @param wx_outTradeNo   商户系统内部的支付订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param wx_outRefundNo  商户系统内部的退款订单号,32个字符内、包含数字与字母,确保在商户系统中唯一
 *  @param wx_refundReason 用户退款理由
 *  @param wx_refundFee    用户欲退款金额，以分为单位
 *  @param block           退款结果回调.如果预退款成功,success=YES;失败success=NO.
 */
+ (void)reqWXRefund:(NSString *)wx_outTradeNo
        outRefundNo:(NSString *)wx_outRefundNo
       refundReason:(NSString *)wx_refundReason
          refundFee:(NSString *)wx_refundFee
           payBlock:(BCPayBlock)block;

/**
 *  同步查询支付订单或退款订单。内置购买只支持查询支付订单表。
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param type    支付平台的支付订单或者退款订单。
 *
 *  @return 符合条件的订单列表
 ("subject",商品名称) ("body",商品描述) ("buyer_id",买家ID) ("buyer_email",买家emai) ("trace_time",订单创建时间)
 ("out_trade_no",商家自定义订单号) ("partner",商家ID) ("refund_status",退款状态)
 ("seller_email",卖家email) ("seller_id",卖家ID) ("total_fee",支付金额) ("trace_id",商户平台用户名)
 ("trade_state",交易状态) ("trace_no",交易流水号) ("refund_finish",退款操作是否完成)
 ("refund_fee",退款金额) ("refund_reason",退款原因) ("reject_reason",拒绝退款原因)
 ("refund_status",退款实时状态)
 @refund status
 REFUND_START = 0; //退款开始
 REFUND_REJECT = 1; //退款被商家拒绝
 REFUND_ACCEPT = 2; //退款被商家同意
 REFUND_SUCCESS = 3; //退款成功
 REFUND_FAIL = 4; //退款被渠道拒绝
 REFUND_RETRY = 5; //退款被渠道拒绝，但原因不明， 需要用原退款单号重试
 REFUND_NEED_OFFLINE = 6; //用户银行卡已注销，现金回流到商户账户，需要走线下人工操作
 */
+ (NSArray *)queryWXPayOrderByKey:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type;

/**
 *  异步查询支付订单或退款订单。内置购买只支持查询支付订单表。
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param type    支付平台的支付订单或者退款订单
 *  @param block 接收查询结果
 */
+ (void)queryWXPayOrderByKeyAsync:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type block:(BCArrayResultBlock)block;

@end