//
//  BCUnionPay.h
//  BCUnionPay
//
//  Created by RInz on 15/3/5.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BeeCloud/BeeCloud.h>

//! Project version number for BCUnionPay.
FOUNDATION_EXPORT double BCUnionPayVersionNumber;

//! Project version string for BCUnionPay.
FOUNDATION_EXPORT const unsigned char BCUnionPayVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <BCUnionPay/PublicHeader.h>


@interface BCUnionPay : NSObject
    
#pragma mark - UnionPay functions
/** @name unionPay functions*/
    
/**
 *  银联在线支付
 *
 *  @param trace_id       支付用户ID，必须保证在商户系统中唯一.可通过trace_id查询订单详情
 *  @param body           商品的标题/交易标题/订单标题/订单关键字等。该参数最长为32个字节(16个汉字)
 *  @param out_trade_no   商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
 *  @param total_fee      支付金额,以分为单位
 *  @param viewController 调起银联支付的页面
 *  @param optional       扩展参数，可以传入任意数量的key/value对来补充对业务逻辑的需求
 *  @param block          接收支付结果回调
 */
+ (void)reqUnionPayment:(NSString *)trace_id
                   body:(NSString *)body
             outTradeNo:(NSString *)out_trade_no
               totalFee:(NSString *)total_fee
         viewController:(UIViewController *)viewController
               optional:(NSDictionary *)optional
               payblock:(BCPayBlock)block ;

/**
 *  银联预退款，支持部分退款或者全额退款。如果提供的支付订单的交易状态不支持退款，在block中返回具体的信息;如果支持退款，生成预退款订单，商户在管理后台管理预退款订单。
 *
 *  @param out_trade_no  商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
 *  @param refund_fee    退款金额
 *  @param out_refund_no 商户系统内部的退款订单号,包含数字与字母,确保在商户系统中唯一
 *  @param refund_reason 退款原因
 *  @param block         接收预退款订单生成结果
 */
+ (void)reqUnionRefund:(NSString *)out_trade_no
             refundFee:(NSString *)refund_fee
           outRefundNo:(NSString *)out_refund_no
          refundReason:(NSString *)refund_reason
           refundBlock:(BCPayBlock)block;

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
+ (NSArray *)queryUPOrderByKey:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type;

/**
 *  异步查询支付订单或退款订单。内置购买只支持查询支付订单表。
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param type    支付平台的支付订单或者退款订单
 *  @param block 接收查询结果
 */
+ (void)queryUPOrderByKeyAsync:(BCPayOrderKey)key value:(NSString *)value orderType:(BCPayOrderType)type block:(BCArrayResultBlock)block;


@end