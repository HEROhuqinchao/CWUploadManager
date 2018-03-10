//
//  CWUploadTask.h
//  uploadFileDemo
//
//  Created by hyjet on 2018/3/9.
//  Copyright © 2018年 uploadFileDemo. All rights reserved.
//

#import <Foundation/Foundation.h>
@class CWFileStreamSeparation;

typedef void(^finishHandler)(CWFileStreamSeparation * _Nullable fileStream, NSError * _Nullable error);

typedef void(^success)(CWFileStreamSeparation * _Nullable fileStream);

@interface CWUploadTask : NSObject

@property (nonatomic,readonly,strong)CWFileStreamSeparation *_Nullable fileStream;
//当前上传任务的URL
@property (nonatomic,readonly,strong)NSURL * _Nullable url;
//当前上传任务的参数
@property (nonatomic,readonly,strong)NSMutableDictionary * _Nullable param;
//任务对象的执行状态
@property (nonatomic,readonly,assign)NSURLSessionTaskState taskState;
//上传任务的唯一ID
@property (nonatomic,readonly,copy)NSString * _Nullable ID;

/**
 根据一个文件分片模型创建一个上传任务，执行 taskResume 方法开始上传
 使用 listenTaskExeCallback 方法传递block进行回调监听
 同时也可以选择实现协议方法进行回调监听
 */
+ (instancetype _Nonnull )initWithStreamModel:(CWFileStreamSeparation * _Nonnull)fileStream;

/**
 监听一个已存在的上传任务的状态
 */
- (void)listenTaskExeCallback:(finishHandler _Nonnull)block
                      success:(success _Nonnull)successBlock;

/**
 根据一个文件分片模型的字典创建一个上传任务(处于等待状态)字典
 */
+ (NSMutableDictionary<NSString*,CWUploadTask*> *_Nullable)uploadTasksWithDict:(NSDictionary<NSString*,CWFileStreamSeparation*> *_Nullable)dict;

/**
 根据一个文件分片模型创建一个上传任务,执行 startExe 方法开始上传,结果会由block回调出来
 */
- (instancetype _Nonnull)initWithStreamModel:(CWFileStreamSeparation *_Nonnull)fileStream
                                      finish:(finishHandler _Nonnull)block
                                     success:(success _Nonnull)successBlock;


//继续/开始上传
- (void)taskResume;

//取消/暂停上传
- (void)taskCancel;


@end