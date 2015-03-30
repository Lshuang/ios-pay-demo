//
//  ShoppingCartTableViewController.m
//  SPayUI
//
//  Created by RInz on 15/3/24.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//
#import "Goods.h"
#import "Optional.h"

#import "ShoppingCartTableViewController.h"
#import "ShoppingCartTableViewCell.h"
#import "ConfirmViewController.h"
#import "CustomInfo.h"

@implementation ShoppingCartTableViewController{
    double totalCost;
    UILabel* totalCostLabel;
}

- (void)viewDidLoad{
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"" style:UIBarButtonItemStylePlain target:nil action:nil];
    self.navigationItem.backBarButtonItem = backButton;
    
    Goods *good1 = [[Goods alloc]init];
    NSMutableAttributedString* description1 = [[NSMutableAttributedString alloc]initWithString:@"裤子\n 蓝色\n 这是条裤裤"];
    [description1 setAttributes:@{NSForegroundColorAttributeName : [UIColor redColor],  NSFontAttributeName : [UIFont systemFontOfSize:17]} range:NSMakeRange(0, 2)];
    [description1 setAttributes:@{NSForegroundColorAttributeName : [UIColor grayColor], NSFontAttributeName : [UIFont systemFontOfSize:11]} range:NSMakeRange(4, 2)];
    good1.goodDescription = description1;
    good1.goodImage = @"yifu";
    good1.goodPrice = @"￥0.01";
    good1.count = 1;
    good1.price = 0.01;
    Goods *good2 = [[Goods alloc]init];
    good2.goodDescription = [[NSMutableAttributedString alloc]initWithString:@"鞋子"];
    good2.goodImage = @"xiezi";
    good2.goodPrice = @"￥90";
    good2.count = 1;
    good2.price = 90.0;
    Goods *good3 = [[Goods alloc]init];
    good3.goodDescription = [[NSMutableAttributedString alloc]initWithString:@"衣服"];
    good3.goodImage = @"kuzi";
    good3.goodPrice = @"￥50";
    good3.count = 1;
    good3.price = 50.0;
    
    totalCost = good1.price + good2.price + good3.price;
    
    self.tableData = [[NSMutableArray alloc]initWithObjects:good1, good2, good3, nil];
    
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    self.tableView.tableFooterView = [[UIView alloc]init];
    self.tableView.backgroundColor = [UIColor colorWithRed:0.97 green:0.97 blue:0.97 alpha:1];
    
    UIView* checkView = [[UIView alloc]initWithFrame:CGRectMake(0, self.view.frame.size.height-40, self.view.frame.size.width, 40)];
    checkView.backgroundColor = [UIColor blackColor];
    [self.view addSubview:checkView];
    
    UIButton* checkButton = [[UIButton alloc]initWithFrame:CGRectMake(checkView.frame.size.width-80, 0, 80, 40)];
    [checkButton setTitle:@"结算" forState:UIControlStateNormal];
    [checkButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    checkButton.backgroundColor = [UIColor redColor];
    [checkView addSubview:checkButton];
    [checkButton addTarget:self action:@selector(check) forControlEvents:UIControlEventTouchDown];
    
    totalCostLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 0, checkView.frame.size.width-10-80, 40)];
    totalCostLabel.text = [NSString stringWithFormat:@"总价：%.2f",totalCost];
    totalCostLabel.textColor = [UIColor whiteColor];
    [checkView addSubview:totalCostLabel];
    
    UIView* addressView = [[UIView alloc]initWithFrame:CGRectMake(0, self.view.frame.size.height-40-40, self.view.frame.size.width, 40)];
    [self.view addSubview:addressView];
    UILabel* addressLabel = [[UILabel alloc]initWithFrame:CGRectMake(0, addressView.frame.size.height/2-10, addressView.frame.size.width, 20)];
    addressLabel.text = @"请输入地址：苏州工业园区若水路388号纳米大学科技园E栋1006 黄君贤";
    addressLabel.textColor = [UIColor blackColor];
    [addressView addSubview:addressLabel];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(addCount:) name:@"addCount" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(removeCount:) name:@"removeCount" object:nil];
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.tableData.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString* cellIdentifier = @"ShoppingCartTableViewCell";
    ShoppingCartTableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier forIndexPath:indexPath];
    
    Goods* good = (Goods*)self.tableData[indexPath.row];
    
    cell.imageView.image = [UIImage imageNamed:good.goodImage];
    cell.describeLabel.attributedText = good.goodDescription;//.text = [NSString stringWithFormat:@"%@", good.goodDescription];
    cell.feeLabel.text = [NSString stringWithFormat:@"%@", good.goodPrice];
    cell.countLabel.text = [NSString stringWithFormat:@"%d", good.count];
    cell.productCount = good.count;
    cell.productPrice = good.price;
    cell.index = indexPath.row;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    if (good.count == 1){
        cell.removeButton.enabled = false;
    }else{
        cell.removeButton.enabled = true;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath{
    NSUInteger row = [indexPath row];
    
    Goods *removeData = self.tableData[row];
    
    [self.tableData removeObjectAtIndex:row];
    [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]withRowAnimation:UITableViewRowAnimationLeft];
    
    totalCost -= removeData.price * removeData.count;
    totalCostLabel.text = [NSString stringWithFormat:@"总价：%.2f",totalCost];
}

- (void)check{
    NSString * storyboardName = @"CheckOutProcess";
    NSString * viewControllerID = @"ConfirmViewController";
    UIStoryboard * storyboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
    ConfirmViewController *confirmViewController = [storyboard instantiateViewControllerWithIdentifier:viewControllerID];
    Optional* yunfei = [[Optional alloc]init];
    yunfei.key = @"运费：";
    yunfei.value = @"￥ 0.0";
    Optional* tax = [[Optional alloc]init];
    tax.key = @"税：";
    tax.value = @"￥ 0.0";
    NSMutableArray* totalArray = [[NSMutableArray alloc]init];
    [totalArray addObjectsFromArray:self.tableData];
    [totalArray addObject:tax];
    [totalArray addObject:yunfei];
    confirmViewController.checkoutData = totalArray;
    confirmViewController.totalCost = totalCost + 0 + 0;
    
    
    CustomInfo* customInfo = [[CustomInfo alloc]init];
    customInfo.outTradeNo = [[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""];
    customInfo.body = [NSString stringWithFormat:@"%@",[[BCUtil generateRandomUUID] stringByReplacingOccurrencesOfString:@"-" withString:@""]];
    customInfo.traceID = @"BeeCloudSPay";
    customInfo.subject = customInfo.outTradeNo;
    customInfo.optional = nil;
    customInfo.aliScheme = @"payUIDemo";
    confirmViewController.customInfo = customInfo;
    
    [self.navigationController pushViewController:confirmViewController animated:YES];
}

- (void)addCount:(NSNotification*) notification{
    double price = (double)[[notification.userInfo objectForKey:@"price"] doubleValue];
    NSInteger row = [[notification.userInfo objectForKey:@"row"] integerValue];
    Goods *good = self.tableData[row];
    good.count += 1;
    self.tableData[row] = good;
    totalCost += price;
    totalCostLabel.text = [NSString stringWithFormat:@"总价：%.2f",totalCost];
}

- (void)removeCount:(NSNotification*) notification{
    double price = (double)[[notification.userInfo objectForKey:@"price"] doubleValue];
    NSInteger row = [[notification.userInfo objectForKey:@"row"] integerValue];
    Goods *good = self.tableData[row];
    good.count -= 1;
    self.tableData[row] = good;
    totalCost -= price;
    totalCostLabel.text = [NSString stringWithFormat:@"总价：%.2f",totalCost];
}

@end
