//
//  ViewController.swift
//  myapp
//
//  Created by z on 2020/7/23.
//  Copyright © 2020 1. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
    //是开始录制 还是暂停录制
    var recStatus:Bool = false;
    //录制按钮
    var btn:NSButton = NSButton(title: "", target: self, action: #selector(myfunc));
    //线程 开始录制的时候，在一个线程里面 结束录制的时候 结束录制
    var thread = Thread();
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        btn.title = "开始录制";
        btn.bezelStyle = .rounded;
        btn.setButtonType(.pushOnPushOff)
        btn.frame = CGRect(x: 320/2-60, y: 240/2-15, width: 130, height: 30);
        self.view.addSubview(btn)
    }

    override var representedObject: Any? {
        didSet {

        }
    }
    @objc func myfunc(){
        recStatus = !recStatus;
        self.btn.title = recStatus ? "停止录制":"开始录制";
        if recStatus {
            thread = Thread(target: self, selector: #selector(recAudio), object: nil)
            thread.start()
        }else{
            set_status(0);
        }
    }
    @objc func recAudio(){
        print("start thread");
        record_audio()
    }

}

