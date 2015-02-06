//
//  BCPay.h
//  BeeCloud
//
//  Created by 健峰 高 on 14-7-29.
//  Copyright (c) 2014年 BeeCloud Inc. All rights reserved.
//

#import <StoreKit/StoreKit.h>

#import "BCConstants.h"
#import "BCObject.h"

/**
 *  BCPay framework provides handy APIs for in-app purchase, WeChat payment. Alipay, and other payment options to come.
 *  
 */
@interface BCPay : BCObject<SKProductsRequestDelegate>

#pragma mark - Properties
/**
 *  The product list obtained from app store, initiated by initProducts.
 */
@property (nonatomic, strong) NSArray *products;

/**
 *  Failed init productIds.
 */
@property (nonatomic, strong) NSArray *failedIds;

#pragma mark - Create instances
/** @name Create New Object */

/**
 *  Get instance of BCPay.
 *
 *  @return instance of BCPay.
 */
+ (instancetype)sharedInstance;

/**
 *  查询某位用户的支付订单，退款订单。内置购买只支持查询支付订单表。
 *
 *  @param traceID 支付用户ID，必须保证在商户系统中唯一.
 *  @param channel 第三方支付平台
 *  @param action  查询支付订单，或者退款订单
 *
 *  @return 订单列表
 */
+ (NSArray *)queryOrderByTraceID:(NSString *)traceID
                         channel:(BCPayChannel)channel
                          action:(BCPayAction)action;

/**
 *  查询某位用户的支付订单，退款订单。不支持查询IAP订单
 *
 *  @param out_trade_no 商户系统内部的订单号,包含数字与字母,确保在商户系统中唯一
 *  @param channel      第三方支付平台标识
 *  @param action       查询支付订单，或者退款订单
 *
 *  @return 订单列表
 */
+ (NSArray *)queryOrderByOutTradeNo:(NSString *)out_trade_no
                            channel:(BCPayChannel)channel
                             action:(BCPayAction)action;

/**
 *  查询某位用户的退款订单。不支持查询IAP订单。
 *
 *  @param refund_no 退款订单号，必须保证在商户系统中唯一.
 *  @param channel   第三方支付平台
 *
 *  @return 订单列表
 */
+ (NSArray *)queryOrderByRefundNo:(NSString *)refund_no
                          channel:(BCPayChannel)channel;

#pragma mark - In-App-Purchase functions
/** @name IAP Get products list,purchase product,restore product*/
 
/**
 *  check whether this device is able or allowed to make payments
 *
 *  @return NO if this device is not able or allowed to make payments
 */
- (BOOL)canMakePay;

/**
 *  Init products.
 *
 *  @param productIds All products app may use.
 *  @param block      The block could be nil for just keep the products in @products, or you can do some init job for
 *                    in-app store init in the block.
 */
- (void)initProducts:(NSArray *)productIds withBlock:(BCProductBlock)block;

/**
 *  Purchase a product.
 *
 *  @param product Product need to purchase.
 *  @param userName Application user name, username in your account system, should be unique for each user.
 *  @param block   Block deal with the purchase result, this should not be null. Notice that if user buy a product
 *                 twice, and the first transaction is not finished, the second one will be ignored.
 */
- (void)purchase:(SKProduct *)product traceID:(NSString *)trace_id withBlock:(BCPurchaseBlock)block;

/**
 *  Purchase a product.
 *
 *  @param productId Product ID need to purchase.
 *  @param userName Application user name, username in your account system, should be unique for each user.
 *  @param block     Block deal with the purchase result, this should not be null. Notice that if user buy a product
 *                   twice, and the first transaction is not finished, the second one will be ignored.
 */
- (void)purchaseWithId:(NSString *)productId traceID:(NSString *)trace_id withBlock:(BCPurchaseBlock)block ;

/**
 *  Restore, for each transaction restored, if transaction.productId in productIds, 
 *  do @BCPurchaseBlock(productId, stateRestored, nil).
 *
 *  @param productIds Products need to be restored.
 *  @param userName Application user name, username in your account system, should be unique for each user.
 *  @param block      Block to deal with the restore callback.
 */
- (void)restore:(NSArray *)productIds traceID:(NSString *)trace_id withBlock:(BCPurchaseBlock)block ;

/**
 *  A method to get a product entity by productId
 *
 *  @param productId Product ID.
 *
 *  @return Product entity.
 */
- (SKProduct *)getProductById:(NSString *)productId;

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

#pragma mark - AliPay Functions
/** @name AliPay Functions */

/**
 *  支付宝支付
 *
 *  @param trace_id     支付用户ID，必须保证在商户系统中唯一.可通过trace_id查询订单详情。
 *  @param out_trade_no 商户系统内部的支付订单号,包含数字与字母,确保在商户系统中唯一
 *  @param subject      商品的标题/交易标题/订单标题/订单关键字等。该参数最长为128个汉字
 *  @param body         对一笔交易的具体描述信息。如果是多种商品,请将商品描 述字符串累加传给body
 *  @param total_fee    该笔订单的资金总额,单位为RMB-Yuan。取值范围为[0.01,100000000.00],精确到小数点后两位
 *  @param scheme       调用支付的app注册在info。plist中的scheme
 *  @param block        支付结果回调.strMsg=@"订单支付成功";//@"正在处理中";@"订单支付失败";@"用户中途取消";@"网络连接错误";
 */
+ (void)reqAliPayment:(NSString *)ali_trace_id
           outTradeNo:(NSString *)ali_out_trade_no
              subject:(NSString *)ali_subject
                 body:(NSString *)ali_body
             totalFee:(NSString *)ali_total_fee
               scheme:(NSString *)ali_scheme
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

#pragma mark - UnionPay functions
/** @name unionPay functions*/

+ (void)reqUnionPayment:(NSString *)trace_id body:(NSString *)body outTradeNo:(NSString *)out_trade_no totalFee:(NSString *)total_fee viewController:(UIViewController *)viewController payblock:(BCPayBlock)block ;
@end
