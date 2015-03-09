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
 *  同步查询内购订单
 *
 *  @param key   根据key查询。trace_id,device_id,product_id
 *  @param value 要查询的值
 *
 *  @return 符合条件的订单列表
 */
+ (NSArray *)queryIAPOrder:(NSString *)key value:(NSString *)value;

/**
 *  异步查询内置购买订单表。
 *
 *  @param key   根据key查询。trace_id,out_trade_no,our_refund_no
 *  @param value 要查询的值
 *  @param block 接收查询结果
 */
+ (void)queryIAPOrderAsync:(NSString *)key value:(NSString *)value
                         block:(BCArrayResultBlock)block;

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

@end
