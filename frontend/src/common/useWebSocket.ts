export enum SendMsgType {
  Init = 'init',
  Click = 'click',
  Surrender = 'surrender',
}

export enum ReceiveMsgType {
  Move = 'move',
  FirstClick = 'firstClick',
  Win = 'win',
  Surrender = 'surrender',
  ValidMoves = 'validMoves',
  Take = 'take',
}

export interface SendMsg {
  type: SendMsgType;
  position?: string;
}

export interface ReceiveMsg {
  type: ReceiveMsgType;
  success?: boolean;
  from?: string;
  to?: string;
  player?: string;
  position?: string;
  validMoves?: {
    x: number;
    y: number;
  }[];
  takeout: string;
}

export function useWebSocket(onMsgCallback: (e: MessageEvent) => void) {
  const ws = new WebSocket('ws://localhost:9002');
  const openWs = async () => {
    return new Promise((resolve, reject) => {
      if (ws.readyState === WebSocket.OPEN) {
        resolve(ws);
      }
      ws.onopen = () => {
        resolve(ws);
      };
      ws.onerror = (e) => {
        reject(e);
      };
    });
  };
  const sendMsg = async (msg: SendMsg) => {
    await openWs();
    ws.send(JSON.stringify(msg));
  };
  ws.onmessage = onMsgCallback;

  return { openWs, sendMsg };
}
