//
//  ShoppingCartTableViewCell.h
//  SPayUI
//
//  Created by RInz on 15/3/24.
//  Copyright (c) 2015年 BeeCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ShoppingCartTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UIImageView *goodsImage;
@property (weak, nonatomic) IBOutlet UILabel *describeLabel;
@property (weak, nonatomic) IBOutlet UILabel *feeLabel;
@property (weak, nonatomic) IBOutlet UIButton *removeButton;
@property (weak, nonatomic) IBOutlet UIButton *addButton;
@property (weak, nonatomic) IBOutlet UILabel *countLabel;

@property int productCount;
@property double productPrice;

@property NSInteger index;


@end
