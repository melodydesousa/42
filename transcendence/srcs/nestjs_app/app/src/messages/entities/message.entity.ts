export class Message {
	senderId: number
	content: string
	chatId: number
}

export class FullMessage {
	createdAt: Date
	nicknameSender: string
	senderId: number
	content: string
	chatId: number
	blocklist: number[]
}