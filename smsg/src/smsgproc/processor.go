package main

import ()

type Message struct {
	UUID        string `json:"UUID"`
	Source      int64  `json:"Source"`
	Destination int64  `json:"Destination"`
	Content     string `json:"Content"`
}

func StartProcessor() {
	for {
		message := Dequeue()
		connID := matchDirective(&message)
		Send(&message, connID)
	}
}

func matchDirective(message *Message) string {
	for dirc := range CONFIG.Directives {
		if !CONFIG.Directives[dirc].JBD && !CONFIG.Directives[dirc].JBS {
			continue
		}

		if CONFIG.Directives[dirc].JBD {
			if !(message.Destination >= CONFIG.Directives[dirc].DRS) ||
				!(message.Destination <= CONFIG.Directives[dirc].DRE) {
				continue
			}
		}

		if CONFIG.Directives[dirc].JBS {
			if !(message.Source >= CONFIG.Directives[dirc].SRS) ||
				!(message.Source <= CONFIG.Directives[dirc].SRE) {
				continue
			}
		}

		STATS.DirectiveHit[CONFIG.Directives[dirc].ConnID]++
		return CONFIG.Directives[dirc].ConnID
	}

	LOG.Noticef("Message %s didn't match any directives. Discarding.", message)
	STATS.DirectiveHit["discard"]++
	return "discard"
}
