package main

import (
	"bytes"
	"database/sql"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"

	_ "modernc.org/sqlite"
)

const (
	codeWhispererBase = "https://q.us-east-1.amazonaws.com"
	defaultProfileArn = "arn:aws:codewhisperer:us-east-1:699475941385:profile/EHGA3GRVQMUK"
	kiroAuthBase      = "https://prod.us-east-1.auth.desktop.kiro.dev"
	dbPath            = "data/kiro2api.db"
)

func main() {
	var token string
	profileArn := defaultProfileArn

	if len(os.Args) >= 2 {
		token = os.Args[1]
	} else {
		db, err := sql.Open("sqlite", dbPath)
		if err != nil {
			fmt.Printf("Failed to open DB: %v\n", err)
			os.Exit(1)
		}
		defer db.Close()

		var accessToken, refreshToken string
		err = db.QueryRow("SELECT COALESCE(access_token,''), COALESCE(refresh_token,'') FROM channel_accounts WHERE channel='kiro' LIMIT 1").Scan(&accessToken, &refreshToken)
		if err != nil {
			fmt.Printf("No kiro account found: %v\n", err)
			os.Exit(1)
		}
		fmt.Printf("DB: access_token len=%d, refresh_token len=%d\n", len(accessToken), len(refreshToken))

		if refreshToken != "" {
			fmt.Println("Refreshing token...")
			newToken, err := refreshAccessToken(accessToken, refreshToken)
			if err != nil {
				fmt.Printf("Refresh failed: %v\nUsing existing token...\n", err)
				token = accessToken
			} else {
				fmt.Printf("Token refreshed! len=%d\n", len(newToken))
				token = newToken
				db.Exec("UPDATE channel_accounts SET access_token=? WHERE channel='kiro'", newToken)
			}
		} else {
			token = accessToken
		}
	}

	if len(os.Args) > 2 {
		profileArn = os.Args[2]
	}

	callListModels(token, profileArn)
}

func refreshAccessToken(accessToken, refreshToken string) (string, error) {
	body, _ := json.Marshal(map[string]string{"refreshToken": refreshToken})
	req, _ := http.NewRequest("POST", kiroAuthBase+"/refreshToken", bytes.NewReader(body))
	req.Header.Set("Content-Type", "application/json")
	if accessToken != "" {
		req.Header.Set("Authorization", "Bearer "+accessToken)
	}
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()
	respBody, _ := io.ReadAll(resp.Body)
	if resp.StatusCode != 200 {
		return "", fmt.Errorf("HTTP %d: %s", resp.StatusCode, string(respBody))
	}
	var result struct {
		AccessToken string `json:"accessToken"`
	}
	json.Unmarshal(respBody, &result)
	if result.AccessToken == "" {
		return "", fmt.Errorf("empty accessToken")
	}
	return result.AccessToken, nil
}

func callListModels(token, profileArn string) {
	u := codeWhispererBase + "/ListAvailableModels"
	params := url.Values{}
	params.Set("origin", "AI_EDITOR")
	params.Set("profileArn", profileArn)
	fullURL := u + "?" + params.Encode()
	fmt.Printf("\nGET %s\n\n", fullURL)

	req, _ := http.NewRequest("GET", fullURL, nil)
	req.Header.Set("Authorization", "Bearer "+token)
	req.Header.Set("Content-Type", "application/json")

	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		os.Exit(1)
	}
	defer resp.Body.Close()
	body, _ := io.ReadAll(resp.Body)
	fmt.Printf("Status: %d\n\n", resp.StatusCode)

	var result map[string]interface{}
	if err := json.Unmarshal(body, &result); err == nil {
		pretty, _ := json.MarshalIndent(result, "", "  ")
		fmt.Println(string(pretty))
	} else {
		fmt.Println(string(body))
	}
}

