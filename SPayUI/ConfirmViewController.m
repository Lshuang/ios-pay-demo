//
//  CheckOutProcessTableViewController.m
//  SPayUI
//
//  Created by RInz on 15/3/25.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import "ConfirmViewController.h"

@interface ConfirmViewController ()

@end

@implementation ConfirmViewController 

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setAutomaticallyAdjustsScrollViewInsets:NO];
    
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"" style:UIBarButtonItemStylePlain target:nil action:nil];
    self.navigationItem.backBarButtonItem = backButton;
    
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.backgroundColor = [UIColor colorWithRed:0.97 green:0.97 blue:0.97 alpha:1];
    
    UIView *confirmView = [[UIView alloc]initWithFrame:CGRectMake(0, self.view.frame.size.height-40, self.view.frame.size.width, 40)];
    confirmView.backgroundColor = [UIColor blackColor];
    [self.view addSubview:confirmView];
    
    UILabel *totalCostLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 0, confirmView.frame.size.width-10-80, 40)];
    totalCostLabel.text = [NSString stringWithFormat:@"总价：%.2f",self.totalCost];
    totalCostLabel.textColor = [UIColor whiteColor];
    [confirmView addSubview:totalCostLabel];
    
//    UIView* addressView = [[UIView alloc]initWithFrame:CGRectMake(0, self.view.frame.size.height-40-40, self.view.frame.size.width, 40)];
//    [self.view addSubview:addressView];
    
    UIButton* confirmButton = [[UIButton alloc]initWithFrame:CGRectMake(confirmView.frame.size.width-80, confirmView.frame.size.height/2-20, 80, 40)];
    [confirmButton setTitle:@"付款" forState:UIControlStateNormal];
    [confirmButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    confirmButton.backgroundColor = [UIColor redColor];
    [confirmView addSubview:confirmButton];
    [confirmButton addTarget:self action:@selector(confirm) forControlEvents:UIControlEventTouchDown];
    
    self.tableView.tableFooterView = [[UIView alloc]init];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.checkoutData.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    if([self.checkoutData[indexPath.row] isKindOfClass:[Goods class]]){
        return 80;
    }else{
        return 40;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    if([self.checkoutData[indexPath.row] isKindOfClass:[Goods class]]){
        ConfirmTableViewCell *checkOutProcessTableViewCell = [tableView dequeueReusableCellWithIdentifier:@"CheckOutProcessTableViewCell" forIndexPath:indexPath];
        Goods *good = self.checkoutData[indexPath.row];
        checkOutProcessTableViewCell.goodImage.image = [UIImage imageNamed:good.goodImage];
        checkOutProcessTableViewCell.goodDescription.attributedText = good.goodDescription;
        checkOutProcessTableViewCell.goodPrice.text = good.goodPrice;
        checkOutProcessTableViewCell.goodCount.text = [NSString stringWithFormat:@"x%d",good.count];
        checkOutProcessTableViewCell.selectionStyle = UITableViewCellSelectionStyleNone;
        
        return checkOutProcessTableViewCell;
    }else{

        [tableView registerNib:[UINib nibWithNibName:@"OptionalTableViewCell" bundle:nil] forCellReuseIdentifier:@"OptionalTableViewCell"];
        OptionalTableViewCell* optionalTableViewCell = [tableView dequeueReusableCellWithIdentifier:@"OptionalTableViewCell" forIndexPath:indexPath];
        Optional* optional = self.checkoutData[indexPath.row];
        optionalTableViewCell.KeyLabel.text = optional.key;
        optionalTableViewCell.ValueLabel.text = optional.value;
        optionalTableViewCell.selectionStyle = UITableViewCellSelectionStyleNone;
        optionalTableViewCell.backgroundColor = [UIColor colorWithRed:0.97 green:0.97 blue:0.97 alpha:1];
        
        return optionalTableViewCell;
    }
}


// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return NO;
}

- (void)confirm{
    NSString * storyboardName = @"CheckOutProcess";
    NSString * viewControllerID = @"CheckOutTableViewController";
    UIStoryboard * storyboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
    CheckOutTableViewController *checkOutTableViewController = [storyboard instantiateViewControllerWithIdentifier:viewControllerID];
    checkOutTableViewController.totalCostLabel.title = [NSString stringWithFormat:@"￥ %.2f",self.totalCost];
    checkOutTableViewController.totalCost = self.totalCost;
    checkOutTableViewController.customInfo = self.customInfo;
    checkOutTableViewController.goodsInfo = self.checkoutData;
    [self.navigationController pushViewController:checkOutTableViewController animated:YES];
}


@end
