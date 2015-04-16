//
//  BCAliPay.h
//  BCAliPay
//
//  Created by RInz on 15/3/5.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>

//! Project version number for BCAliPay.
FOUNDATION_EXPORT double BCAliPayVersionNumber;

//! Project version string for BCAliPay.
FOUNDATION_EXPORT const unsigned char BCAliPayVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <BCAliPay/PublicHeader.h>


@interface BCAliPay : NSObject

#pragma mark - AliPay Functions
/** @name AliPay Functions */

+ (BOOL)handleOpenUrl:(NSURL *)url;

/**
 *  支付宝支付
 *
 *  @param trace_id     支付用户ID，必须保证在商户系统中唯一.可通过trace_id查询订单详情。
 *  @param out_trade_no 商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一,该参数最长为64个字符
 *  @param subject      商品的标题/交易标题/订单标题/订单关键字等。该参数最长为128个汉字
 *  @param body         对一笔交易的具体描述信息。如果是多种商品,请将商品描 述字符串累加传给body
 *  @param total_fee    该笔订单的资金总额,单位为RMB-Yuan。取值范围为[0.01,100000000.00],精确到小数点后两位
 *  @param scheme       调用支付的app注册在info。plist中的scheme
 *  @param optional     扩展参数，可以传入任意数量的key/value对来补充对业务逻辑的需求
 *  @param block        支付结果回调.strMsg=@"订单支付成功";//@"正在处理中";@"订单支付失败";@"用户中途取消";@"网络连接错误";
 */
+ (void)reqAliPayment:(NSString *)ali_trace_id
           outTradeNo:(NSString *)ali_out_trade_no
              subject:(NSString *)ali_subject
                 body:(NSString *)ali_body
             totalFee:(NSString *)ali_total_fee
               scheme:(NSString *)ali_scheme
             optional:(NSDictionary *)optional
             payBlock:(BCPayBlock)block;

/**
 *  根据out_trade_no，refund_no, refund_reason,refund_fee查询订单是否可退款，允许退款情况下自动生成预退款订单，否则返回不可退款原因。预退款订单生成成功后，在BeeCloud商户后台对预退款订单进行处理。（订单状态trade_status=@”TRADE_SUCCESS“)时支持退款，其他状态下不支持退款。
 *
 *  @param out_trade_no  商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
 *  @param refund_no     格式为:退款日期(8位)+流水号(3~8位)。不可重复,且退款日期必须是当天日期(年月日)。
 *                       流水号可以接受数字或英文字符,建议使用数字,但不可接受“000”。例如: 201101120001
 *  @param refund_fee    退款金额
 *  @param refund_reason 退款原因
 *  @param block         退款结果回调
 */
+ (void)reqAliRefund:(NSString *)ali_out_trade_no
            refundNo:(NSString *)ali_refund_no
           refundFee:(NSString *)ali_refund_fee
        refundReason:(NSString *)ali_refund_reason
         refundBlock:(BCPayBlock)block;

/**
 *  同步查询支付订单或退款订单
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
+ (NSArray *)queryAliOrderByKey:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type;

/**
 *  异步查询支付订单或退款订单
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param type    支付平台的支付订单或者退款订单
 *  @param block 接收查询结果
 */
+ (void)queryAliOrderByKeyAsync:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type block:(BCArrayResultBlock)block;

@end